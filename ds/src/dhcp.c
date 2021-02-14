/******************************************************************************* 
 * Description: Implemention of Dynamic Host Configuration Protocol            *
 * Author: Noa Efrati                                                          *
 * Reviewer: Yifat Baruch                                                      *
 * Date: 12.01.2021                                                            *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

#include <stdlib.h>      /* malloc, free                                      */
#include <assert.h>      /* assert                                            */
#include "dhcp.h"        /* DHCP API                                          */
#include <limits.h>      /* CAHR_BIT                                          */

#include POW2(depth) (1UL << depth) 
#define IPV4_LEN 4
#define FREE(x) free(x); x = NULL;
#define TOTAL_BITS CHAR_BIT * IPV4_LEN

/******************************************************************************/
/***                         Structs & Typedefs                             ***/
/******************************************************************************/

typedef enum {ZERO = 0, ONE = 1} direction_t;    
	
typedef struct node node_t;
	
struct node
{
   node_t *children[2];
   int is_taken;
};
    
struct dhcp
{
	ipv4_t ip_prefix; 
	size_t prefix_length;
    node_t root;
};

/******************************************************************************/
/***                   Private Functions Declerations                       ***/
/******************************************************************************/

static int IsFullLeaf(node_t *node);
static size_t CountFull(node_t *node);

static int IsTakenNodeParent(node_t *node);
static void UpdateIP(ipv4_t *ip, size_t depth);
static dhcp_status_t AllocIPRec(node_t *node, 
								size_t depth, 
                                ipv4_t *preferred_ip);

static node_t *CreateNode(void);
static void DestroyNodes(node_t *node);
static dhcp_status_t InitSystemAddresses(dhcp_t *dhcp,
                                         ipv4_t network_address,
                                         ipv4_t server_address,
                                         ipv4_t broadcast_address);

static direction_t GetBitAtIndex(ipv4_t ip,  size_t index);
static void SetBitAtIndex(ipv4_t *ip, size_t index, direction_t direction);
static dhcp_status_t FreeImp(node_t *node, size_t depth, ipv4_t ip_to_free);

/******************************************************************************/
/***                            API Defenitions                             ***/
/******************************************************************************/

dhcp_t* DHCPCreate(ipv4_t subnet, size_t prefix_length)
{
	dhcp_t *dhcp = NULL;
	ipv4_t network_address = {{0,0,0,0}};
	ipv4_t server_address = {{255, 255, 255, 254}};
    ipv4_t broadcast_address = {{255, 255, 255, 255}};

	assert(prefix_length < TOTAL_BITS);
	
	dhcp = calloc(1, sizeof(dhcp_t));
	
	if (NULL != dhcp)
	{
		dhcp->ip_prefix = subnet;
		dhcp->prefix_length = prefix_length;
	
		if (SUCCESS != InitSystemAddresses(dhcp, network_address,
		                                    server_address, broadcast_address))
		{
			return NULL;
		}
	}
	
	return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(dhcp);
	                                         /* set null to the filed*/
	DestroyNodes(dhcp->root.children[ZERO]); dhcp->root.children[ZERO] = NULL;
	DestroyNodes(dhcp->root.children[ONE]); dhcp->root.children[ONE] = NULL;
	FREE(dhcp);
}

dhcp_status_t DHCPAllocateIP(dhcp_t *dhcp, ipv4_t preferred_ip, ipv4_t *_result)
{
	size_t i = 0;
	size_t depth = 0;
	dhcp_status_t status = SUCCESS;
	ipv4_t error_ip = {{0, 0, 0, 0}};
	
	assert(dhcp);
	assert(_result);
	
	depth = TOTAL_BITS - dhcp->prefix_length;
	 
	for (;i < dhcp->prefix_length; ++i)
	{
		SetBitAtIndex(&preferred_ip, i, GetBitAtIndex(dhcp->ip_prefix,i));
	}
	
	status = AllocIPRec(&dhcp->root, depth, &preferred_ip);
	
	*_result = (status == SUCCESS) ? (preferred_ip) : (error_ip);
	
	return status;
}

dhcp_status_t DHCPFreeIP(dhcp_t *dhcp, ipv4_t ip_to_free)
{
	size_t depth = 0;
	
	assert(dhcp);
	
	depth = TOTAL_BITS - dhcp->prefix_length;
	
	return FreeImp(&dhcp->root, depth, ip_to_free);
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
	size_t depth = 0;
	
	assert(dhcp);
	
	depth = TOTAL_BITS - dhcp->prefix_length;	                          
	
	 /* (2 ^ (32 - prefix len)) - (all the taken nodes)*/
	return (1UL << depth) - CountFull((node_t *)&dhcp->root);				
}
/*********************** Private Functions Defenitions ************************/

static dhcp_status_t InitSystemAddresses(dhcp_t *dhcp, 
                                         ipv4_t network_address, 
                                         ipv4_t server_address,
                                         ipv4_t broadcast_address)
{
	ipv4_t return_ip = {{0,0,0,0}};
	dhcp_status_t return_status = SUCCESS;
	
	assert(dhcp);
	
	return_status = DHCPAllocateIP(dhcp, network_address, &return_ip);
	
	if (SUCCESS != return_status)
	{
		DHCPDestroy(dhcp);
		
		return return_status;
	}
	
	return_status = DHCPAllocateIP(dhcp, server_address, &return_ip);
	
	if (SUCCESS != return_status)
	{
		DHCPDestroy(dhcp);
		
		return return_status;
	}
	
	return_status = DHCPAllocateIP(dhcp, broadcast_address, &return_ip);
	
	if (SUCCESS != return_status)
	{
		DHCPDestroy(dhcp);
		
		return return_status;
	}
	
	return return_status;
}
static node_t *CreateNode(void)
{
	node_t *node = (node_t *) malloc(sizeof(node_t));
	if (NULL != node)
	{
		node->children[ZERO] = NULL;
		node->children[ONE] = NULL;
		node->is_taken = 0;
	}
	
	return node;
}

/* post order destroy- first the leaves */
static void DestroyNodes(node_t *node)
{
	/* reached a leaf */
	if (NULL == node)
	{
		return;
	}
	/* left child  */
	DestroyNodes(node->children[ZERO]); node->children[ZERO] = NULL;
	/* right child */ 
	DestroyNodes(node->children[ONE]); node->children[ONE] = NULL;  
	
	FREE(node);
}

static dhcp_status_t AllocIPRec(node_t *node, 
								size_t depth,
                                ipv4_t *preferred_ip)
{
	direction_t direction = 0;
	dhcp_status_t status = 0;
	
	assert(node);
	assert(preferred_ip);
	
	if (node->is_taken)
	{
		return DHCP_FULL;
	}
	
	/* The lowest level was reached out*/
	if (0 == depth)
	{
		node->is_taken = 1;
		
		return SUCCESS;
	}
	
	direction = GetBitAtIndex(*preferred_ip, TOTAL_BITS - depth);
	
	if (NULL == node->children[direction]) 
	{
			node->children[direction] = CreateNode();
			
			if (NULL == node->children[direction])
			{
				return MEM_ALLOC_ERROR;
			}
	}
	
	status =  AllocIPRec(node->children[direction], depth - 1, preferred_ip);
	
	/* if dhcp is full and the requested direction is zero (and taken as well), 
	 * than check if node in the 'one' direction is'nt taken - 
	 * if it true: create this node.
	 * finally update preferred_ip.                             
     */
	if (DHCP_FULL == status && ZERO == direction)
    {
    	if (NULL == node->children[ONE])
    	{
    		node->children[ONE] = CreateNode();
    		
    		if (NULL == node->children[ONE])
    		{
    			return MEM_ALLOC_ERROR;
    		}
    	}
    	
    	UpdateIP(preferred_ip, depth);
    	status = AllocIPRec(node->children[ONE], depth - 1 ,preferred_ip);
    }
    							 
    node->is_taken = IsTakenNodeParent(node);							 
	
	return status;
}

static void UpdateIP(ipv4_t *ip, size_t depth)
{
	size_t i = TOTAL_BITS - depth;
	
	SetBitAtIndex(ip, i, ONE);
	
	for (i = i + 1; i < TOTAL_BITS; ++i)
	{
		SetBitAtIndex(ip, i, ZERO);
	}
}

static void SetBitAtIndex(ipv4_t *ip, size_t index, direction_t direction)
{
	size_t offset = (CHAR_BIT - (index % CHAR_BIT) - 1);
	size_t cell = index/CHAR_BIT;
	
	ip->ip[cell] = (ip->ip[cell] & ~(1UL << offset)) | (direction << offset);
}

static direction_t GetBitAtIndex(ipv4_t ip,  size_t index)
{
	size_t offset = (CHAR_BIT - (index % CHAR_BIT) - 1);
	size_t cell = index/ CHAR_BIT;
	
	return ip.ip[cell] >> offset & 1UL;
}
static int IsTakenNodeParent(node_t *node)
{
	assert(node);
	
	return (NULL != node->children[ZERO] && node->children[ZERO]->is_taken &&
		    NULL != node->children[ONE] && node->children[ONE]->is_taken);
}
static dhcp_status_t FreeImp(node_t *node, size_t depth, ipv4_t ip_to_free)
{
	direction_t direction = 0;
	dhcp_status_t status = 0; 

	if (0 == depth)
	{	
		if (node->is_taken)
		{
			node->is_taken = 0;
			
			return SUCCESS;
		}
		else
		{
			return NOT_ALLOCATED;
		}		
	}

	direction = GetBitAtIndex(ip_to_free, TOTAL_BITS - depth);

	if (NULL == node->children[direction])
	{
		return NOT_ALLOCATED;
	}
	/* in case is allocated */
	status =  FreeImp(node->children[direction], depth - 1,ip_to_free);	
	
	node->is_taken = IsTakenNodeParent(node);	
	
	return status;
}
/* after getting to the deepest level : 
 * in the way up - need to mark the node with ZERO and ONE children -
 * (which is taken and exist) as a taken node parent that is taken in itself*/

static size_t CountFull(node_t *node)
{
	if (NULL == node)
	{
		return (0);
	}
	
	return (IsFullLeaf(node) + 
		   CountFull(node->children[ZERO]) + CountFull(node->children[ONE]));
	
}
static int IsFullLeaf(node_t *node)
{
	assert(node);
	
	return (node->is_taken &&
	 		NULL == node->children[ZERO] && NULL == node->children[ONE]);
}	
