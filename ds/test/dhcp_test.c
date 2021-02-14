/*************************************************************************** 
 * Description: Testing of Implementation of DHCP
 * Author: Oriel Nofekh
 *
 * Infinity Labs OL97
 ***************************************************************************/


#include <stdio.h>     /* printf */
#include <assert.h>    /* assert */
#include "dhcp.h"      /* DHCP API */


/******************************************************************************/
/***                        Color Defines   		                      ***/
/******************************************************************************/
#define DEF     "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

static int test_counter_g = 0;
static int success_counter_g = 0;

#define TEST(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEF, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define TESTC(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %c, Expected: %c\n" DEF, name, __LINE__, (char) (real), (char) (expected)); \
    } while (0)

#define TESTIP(name, real, expected) \
    do { \
        ++test_counter_g; \
        if ((real).ip[0] == (expected).ip[0] && (real).ip[1] == (expected).ip[1] && \
           (real).ip[2] == (expected).ip[2] && (real).ip[3] == (expected).ip[3]) \
        { \
        ++success_counter_g; \
        } \
        else \
        { \
        printf(RED "%s, Failed on line %d, Real: ", name, __LINE__); \
        PrintIP(real); \
        printf(", Expected: "); \
        PrintIP(expected); \
        printf("\n" DEF); \
        } \
    } while (0)

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)



/************************* Testing Functions *************************/

static ipv4_t GetIPV4(int x0, int x1, int x2, int x3)
{
	ipv4_t ip = {{0,0,0,0}};
	ip.ip[0] = x0;
	ip.ip[1] = x1;
	ip.ip[2] = x2;
	ip.ip[3] = x3;
	return ip;
}

static void PrintIP(ipv4_t ip)
{
	printf("%d.%d.%d.%d", (int) ip.ip[0], (int) ip.ip[1], 
	                      (int) ip.ip[2], (int) ip.ip[3]);
}

static void TestCreateDestroy(void)
{
	ipv4_t subnet = {{192,0,0,0}};
	size_t prefix_length = 8;
	
	dhcp_t *dhcp = DHCPCreate(subnet, prefix_length);
	
	DHCPDestroy(dhcp);
	
	printf(BOLDBLUE "Completed TestCreateDestroy\n" DEF);
}

static void TestCreateDestroyAdvanced(void)
{
	dhcp_t *dhcp = NULL;
	ipv4_t subnet0 = {{0,0,0,0}};
	ipv4_t subnet1 = {{128,0,0,0}};
	ipv4_t subnet3 = {{32,0,0,0}};
	ipv4_t subnet8 = {{192,0,0,0}};
	ipv4_t subnet9 = {{192,128,0,0}};
	ipv4_t subnet15 = {{192,2,0,0}};
	ipv4_t subnet30 = {{192,125,131,8}};
	
	dhcp = DHCPCreate(subnet0, 0);
	DHCPDestroy(dhcp);
	
	dhcp = DHCPCreate(subnet1, 1);
	DHCPDestroy(dhcp);
	
	dhcp = DHCPCreate(subnet3, 3);
	DHCPDestroy(dhcp);
	
	dhcp = DHCPCreate(subnet8, 8);
	DHCPDestroy(dhcp);
	
	dhcp = DHCPCreate(subnet9, 9);
	DHCPDestroy(dhcp);
	
	dhcp = DHCPCreate(subnet15, 15);
	DHCPDestroy(dhcp);
	
	dhcp = DHCPCreate(subnet30, 30);
	DHCPDestroy(dhcp);
	
	printf(BOLDBLUE "Completed TestCreateDestroyAdvanced\n" DEF);
}

static void Test1(void)
{
	size_t prefix_length = 8;
	ipv4_t subnet = {{192,0,0,0}};
	
	dhcp_status_t status = SUCCESS;
	ipv4_t alloced_ip = {{0,0,0,0}};
	ipv4_t preferred_ip = {{0,0,0,0}};
	ipv4_t expected_ip = {{0,0,0,0}};
	
	dhcp_t *dhcp = DHCPCreate(subnet, prefix_length);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	
	
	preferred_ip = GetIPV4(192,0,0,0);
	expected_ip = GetIPV4(192,0,0,1);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(192,255,255,254);
	expected_ip = GetIPV4(0,0,0,0);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, DHCP_FULL);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(192,255,255,255);
	expected_ip = GetIPV4(0,0,0,0);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, DHCP_FULL);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(192,0,0,77);
	expected_ip = GetIPV4(192,0,0,77);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	preferred_ip = GetIPV4(192,16,15,12);
	expected_ip = GetIPV4(192,16,15,12);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 6);
	
	preferred_ip = GetIPV4(192,0,0,77);
	expected_ip = GetIPV4(192,0,0,78);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 7);
	
	preferred_ip = GetIPV4(192,0,0,77);
	expected_ip = GetIPV4(192,0,0,79);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 8);
	
	
	
	DHCPDestroy(dhcp);
	
	printf(BOLDBLUE "Completed Test1\n" DEF);
}

static void Test2(void)
{
	ipv4_t subnet = {{192,0,0,0}};
	size_t prefix_length = 8;
	
	dhcp_status_t status = SUCCESS;
	ipv4_t alloced_ip = {{0,0,0,0}};
	ipv4_t preferred_ip = {{0,0,0,0}};
	ipv4_t expected_ip = {{0,0,0,0}};
	ipv4_t ip_to_remove = {{0,0,0,0}};
	
	dhcp_t *dhcp = DHCPCreate(subnet, prefix_length);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	
	
	preferred_ip = GetIPV4(192,0,0,12);
	expected_ip = GetIPV4(192,0,0,12);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(192,0,0,12);
	expected_ip = GetIPV4(192,0,0,13);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	preferred_ip = GetIPV4(192,27,11,17);
	expected_ip = GetIPV4(192,27,11,17);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 6);
	
	preferred_ip = GetIPV4(192,32,111,22);
	expected_ip = GetIPV4(192,32,111,22);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 7);
	
	
	
	ip_to_remove = GetIPV4(192,0,0,12);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 6);
	
	ip_to_remove = GetIPV4(192,0,0,13);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	ip_to_remove = GetIPV4(192,0,0,14);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	ip_to_remove = GetIPV4(192,0,0,12);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	ip_to_remove = GetIPV4(192,27,11,17);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	
	
	DHCPDestroy(dhcp);
	
	printf(BOLDBLUE "Completed Test2\n" DEF);
}

static void Test3(void)
{
	size_t prefix_length = 8;
	ipv4_t subnet = {{192,0,0,0}};
	
	dhcp_status_t status = SUCCESS;
	ipv4_t alloced_ip = {{0,0,0,0}};
	ipv4_t preferred_ip = {{0,0,0,0}};
	ipv4_t expected_ip = {{0,0,0,0}};
	
	dhcp_t *dhcp = DHCPCreate(subnet, prefix_length);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(192,0,0,1);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(192,0,0,2);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(192,0,0,3);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 6);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(192,0,0,4);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 7);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(192,0,0,5);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 8);
	
	
	
	DHCPDestroy(dhcp);
	
	printf(BOLDBLUE "Completed Test3\n" DEF);
}

static void Test4(void)
{
	dhcp_t *dhcp = NULL;
	ipv4_t subnet = {{64,0,0,0}};
	size_t prefix_length = 0;
	
	dhcp_status_t status = SUCCESS;
	ipv4_t alloced_ip = {{0,0,0,0}};
	ipv4_t preferred_ip = {{0,0,0,0}};
	ipv4_t expected_ip = {{0,0,0,0}};
	ipv4_t ip_to_remove = {{0,0,0,0}};
	
	/*************** prefix length = 0 ***************/
	prefix_length = 0;
	dhcp = DHCPCreate(subnet, prefix_length);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(0,0,0,1);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(0,0,0,2);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	ip_to_remove = GetIPV4(0,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	ip_to_remove = GetIPV4(0,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	DHCPDestroy(dhcp);
	
	/*************** prefix length = 1 ***************/
	prefix_length = 1;
	dhcp = DHCPCreate(subnet, prefix_length);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(0,0,0,1);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(0,0,0,2);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	ip_to_remove = GetIPV4(0,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	ip_to_remove = GetIPV4(0,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	DHCPDestroy(dhcp);
	
	/*************** prefix length = 3 ***************/
	prefix_length = 3;
	dhcp = DHCPCreate(subnet, prefix_length);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(64,0,0,1);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(64,0,0,2);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	ip_to_remove = GetIPV4(64,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	ip_to_remove = GetIPV4(64,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	DHCPDestroy(dhcp);
	
	/*************** prefix length = 9 ***************/
	prefix_length = 9;
	dhcp = DHCPCreate(subnet, prefix_length);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(64,0,0,1);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(64,0,0,2);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	ip_to_remove = GetIPV4(64,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	ip_to_remove = GetIPV4(64,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	DHCPDestroy(dhcp);
	
	/*************** prefix length = 15 ***************/
	prefix_length = 15;
	dhcp = DHCPCreate(subnet, prefix_length);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(64,0,0,1);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(64,0,0,2);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	ip_to_remove = GetIPV4(64,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	ip_to_remove = GetIPV4(64,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	DHCPDestroy(dhcp);
	
	/*************** prefix length = 30 ***************/
	/* there are only 4 hosts available, and 3 of them were assigned in Create */
	prefix_length = 30;
	dhcp = DHCPCreate(subnet, prefix_length);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(64,0,0,1);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(0,0,0,0);
	expected_ip = GetIPV4(0,0,0,0);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, DHCP_FULL);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	ip_to_remove = GetIPV4(64,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	ip_to_remove = GetIPV4(64,0,0,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	DHCPDestroy(dhcp);
	
	printf(BOLDBLUE "Completed Test4\n" DEF);
}

static void Test5(void)
{
	size_t prefix_length = 25;
	ipv4_t subnet = {{11,22,33,0}};
	
	dhcp_status_t status = SUCCESS;
	ipv4_t alloced_ip = {{0,0,0,0}};
	ipv4_t preferred_ip = {{0,0,0,0}};
	ipv4_t expected_ip = {{0,0,0,0}};
	ipv4_t ip_to_remove = {{0,0,0,0}};
	
	dhcp_t *dhcp = DHCPCreate(subnet, prefix_length);
	
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	
	
	preferred_ip = GetIPV4(11,22,33,1);
	expected_ip = GetIPV4(11,22,33,1);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	preferred_ip = GetIPV4(11,22,33,5);
	expected_ip = GetIPV4(11,22,33,5);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	preferred_ip = GetIPV4(11,22,33,5);
	expected_ip = GetIPV4(11,22,33,6);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 6);
	
	preferred_ip = GetIPV4(11,22,33,8);
	expected_ip = GetIPV4(11,22,33,8);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 7);
	
	preferred_ip = GetIPV4(11,22,33,10);
	expected_ip = GetIPV4(11,22,33,10);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 8);
	
	preferred_ip = GetIPV4(11,22,33,11);
	expected_ip = GetIPV4(11,22,33,11);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 9);
	
	preferred_ip = GetIPV4(11,22,33,13);
	expected_ip = GetIPV4(11,22,33,13);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 10);
	
	preferred_ip = GetIPV4(11,22,33,15);
	expected_ip = GetIPV4(11,22,33,15);
	status = DHCPAllocateIP(dhcp, preferred_ip, &alloced_ip);
	TEST("AllocIP Success", status, SUCCESS);
	TESTIP("AllocIP Value", alloced_ip, expected_ip);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 11);
	
	
	
	ip_to_remove = GetIPV4(11,22,33,1);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 10);
	
	ip_to_remove = GetIPV4(11,22,33,13);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 9);
	
	ip_to_remove = GetIPV4(11,22,33,15);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 8);
	
	ip_to_remove = GetIPV4(11,22,33,8);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 7);
	
	ip_to_remove = GetIPV4(11,22,33,10);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 6);
	
	ip_to_remove = GetIPV4(11,22,33,11);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 5);
	
	ip_to_remove = GetIPV4(11,22,33,5);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 4);
	
	ip_to_remove = GetIPV4(11,22,33,6);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, SUCCESS);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	
	
	ip_to_remove = GetIPV4(11,22,33,5);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	ip_to_remove = GetIPV4(11,22,33,6);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	ip_to_remove = GetIPV4(11,22,33,11);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	ip_to_remove = GetIPV4(11,22,33,13);
	status = DHCPFreeIP(dhcp, ip_to_remove);
	TEST("AllocIP Success", status, NOT_ALLOCATED);
	TEST("CountFree", DHCPCountFree(dhcp), (1UL << (32 - prefix_length)) - 3);
	
	
	
	DHCPDestroy(dhcp);
	
	printf(BOLDBLUE "Completed Test5\n" DEF);
}

/************************* main function *************************/

int main(void)
{
	/* just Creates and Destroys */
	TestCreateDestroy();
	
	/* just Creates and Destroys, but with various parameters */
	TestCreateDestroyAdvanced();
	
	/* only alloc, without free */
	Test1();
	
	/* both alloc and free */
	Test2();
	
	/* alloc with {{0,0,0,0}} as parameter */
	Test3();
	
	/* till now, we used prefix_length = 8 in all tests
	   (except for Advanced Create-Destroy),
	   so let's try it with all kinds of prefix lengths */
	Test4();
	
	/* let's try to create a relatively complicated tree and 
	   see if things still work as they should */
	Test5();
	
	PASS;
	
	return 0;
}




















