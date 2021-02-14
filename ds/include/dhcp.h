#ifndef __DHCP_H_OL97_ILRD__
#define __DHCP_H_OL97_ILRD__

/*******************************************************************************
 * Header file Containing DHCP Declarations.
 *
 * Infinity Labs - OL97                                                      
 ******************************************************************************/
 
/******************************************************************************/
/***                               Includes                                 ***/
/******************************************************************************/
#include <stddef.h> /* size_t */

/******************************************************************************/
/***                               Typedefs                                 ***/
/******************************************************************************/
typedef struct
{
	unsigned char ip[4];
} ipv4_t;

typedef enum 
{
	SUCCESS = 0, 
	MEM_ALLOC_ERROR, 
	DHCP_FULL,
	NOT_ALLOCATED
} dhcp_status_t;

typedef struct dhcp dhcp_t;

/*
    Inside the implementation file:
    ==============================
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
*/

/******************************************************************************/
/***                            API Declarations                            ***/
/******************************************************************************/

/*
 * Description: This function is used for creating a DHCP management strucure,
 * the user provides the ip subnet and the prefix size, the remaining bits 
 * (num of bits in IPV4 - prefix) are reserved for the inner network addresses 
 * managed by the DHCP. In the creation process 3 special addresses are reserved 
 * for: Network (X0...00), Server (X1...10) & Broadcast (X1...11).
 * Return Value: Pointer to initialized DHCP structure, or NULL if there was
 * a memory allocation error.
 * UB: if prefix_length is bigger than (num of bits in IPV4 - 2)
 * Time complexity: O(Log (n)).
 */
dhcp_t* DHCPCreate(ipv4_t subnet, size_t prefix_length);

/*
 * Description: This function is used for destroying a DHCP strucure, and free
 * all allocated memory.
 * Return Value: None.
 * Time complexity: O(n).
 */
void DHCPDestroy(dhcp_t *dhcp);

/*
 * Description: This function is used for assigning a new and free IP address to
 * the user. The user can pass a preferred IP address, in which case the DHCP 
 * provide the smallerst address that is equal or bigger to the preferred one. 
 * The user is not obligated to provide a preferred address, she can just pass 
 * {0,0,0,0}, so the DHCP will allocate the first free address.
 * Return Value: On success, Assigned ip address will be set inside _result and 
 * SUCCESS status will be returned, in case all IP addresses are already 
 * assigned, DHCP_FULL will be returned, in case no free memory is availiable, 
 * MEM_ALLOC_ERROR will be returned. In all cases of failure, the value
 * of _result would be set to 0.0.0.0.
 * UB: if the preferred_ip is not 0.0.0.0 and does not start with subnet.
 * Time complexity: O(Log (n)).
 */
dhcp_status_t DHCPAllocateIP(dhcp_t *dhcp, ipv4_t preferred_ip, ipv4_t *_result);

/*
 * Description: This function is used by the user for releasing an IP address.
 * Return Value: status of execution (SUCCESS, NOT_ALLOCATED).
 * UB: if ip_to_free does not start with subnet.
 * Time complexity: O(Log (n)).
 */
dhcp_status_t DHCPFreeIP(dhcp_t *dhcp, ipv4_t ip_to_free);

/*
 * Description: This function is used for counting the amount of free IP's.
 * Return Value: The amount of free IP's left to allocate.
 * Time complexity: O(n).
 */
size_t DHCPCountFree(const dhcp_t *dhcp);

#endif /* __DHCP_H_OL97_ILRD__ */			
