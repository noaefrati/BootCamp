/*************************************************************************** 
 * Description: Test Queue Functions                                       *
 * Author: Noa Efrati                                                      *
 * Reviewer:                                                               *
 * Date: 25.11.20                                                          *
 * Infinity Labs OL97                                                      *
 ***************************************************************************/


#include "slist.h"               /* singly linked list functions           */
#include "queue.h"               /* queue functions                        */
#include <stdio.h>               /* printf                                 */
#include <string.h>              /* strlen                                 */
#define RED     "\033[31m"       /* Red                                    */
#define GREEN   "\033[32m"       /* Green                                  */
#define DEF   "\033[0m"

#define TEST(name, real, expected) (real == expected) ?\
printf(GREEN"%s, SUCCESS in line %d\n"DEF, name, __LINE__)\
: printf(RED"%s, FAIL in line %d\n"DEF, name, __LINE__)

void QTest(void);
/*void QAppendTest(void);*/

int main()
{
	 QTest();
	return (0);
}
void QTest(void)
{
	queue_t *q = QCreate();
	char *str = "hello world!";
	size_t size = strlen(str), i = 0;
	
	
	if (NULL == q)
	{
		TEST("QCreateDestroyTest ", -1, 1);
	}
	
	for (; size > i; ++i)
	{
		QEnqueue(q, str + i);
	}
	TEST("QEnqueueTest ", QSize(q), strlen(str));
	
	for (i = 0; 3 > i; ++i)
	{
		QDequeue(q);
	}
	TEST("QEnqueueTest ", QSize(q), (strlen(str) - 3));
	
	
	QDestroy(q);
	
}
