/*************************************************************************** 
 * Description: Testing of Implementation of Hash Table
 * Author: Oriel Nofekh
 *
 * Infinity Labs OL97
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>	/*for tolower*/
#include <string.h>	/*for strcmp*/
#include <stdio.h>         /* printf */
#include <assert.h>        /* assert */
#include "hash_table.h"    /* Hash Table API */

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


#define NUM_LETTERS_IN_ABC 26
#define DICT_PATH ("/usr/share/dict/american-english")
#define DICTIONARY_SIZE 102306
#define ERROR (printf("\nError in line: %d",__LINE__))
#define SIZE 5381
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

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)



/************************* Helper Functions *************************/

typedef struct
{
	unsigned int id;
	char grade;
} student_t;

static const size_t TABLE_SIZE = 100;

static size_t HashFunc(const void *data)
{
	student_t *student = (student_t *) data;
	
	return student->id % TABLE_SIZE;
}

static int MatchFunc(const void *one, const void *other)
{
	student_t *student_one = (student_t *) one;
	student_t *student_other = (student_t *) other;
	
	return (student_one->id == student_other->id);
}

static int ActionLowerGrade(void *data, void *params)
{
	student_t *student = (student_t *) data;
	
	student->grade += 1;   /* e.g. lowers the grade from A to B */
	
	(void) params;
	
	return 0;
}

static int ActionIsFailed(void *data, void *params)
{
	student_t *student = (student_t *) data;
	
	(void) params;
	
	return student->grade == 'F';   /* F is failed */
}

static int ActionChangeGrade(void *data, void *params)
{
	student_t *student = (student_t *) data;
	
	student->grade = *(char *) params;
	
	return 0;
}

/************************* Tests Functions *************************/

static void TestCreateDestroy(void)
{
	hash_table_t *ht = HTCreate(HashFunc, MatchFunc, TABLE_SIZE);
	
	HTDestroy(ht);
	
	printf(BOLDBLUE "Completed TestCreateDestroy\n" DEF);
}

static void Test1(void)
{
	int status = 0;
	char new_grade = 'L';
	
	hash_table_t *ht = HTCreate(HashFunc, MatchFunc, TABLE_SIZE);
	
	student_t key_student = {0, '\0'};
	student_t *student = NULL;
	
	student_t class[10];
	class[0].id = 257;
	class[0].grade = 'A';
	class[1].id = 32;
	class[1].grade = 'B';
	class[2].id = 111;
	class[2].grade = 'E';
	class[3].id = 104701;
	class[3].grade = 'C';
	class[4].id = 57;
	class[4].grade = 'D';
	class[5].id = 1057;
	class[5].grade = 'X';
	class[6].id = 2057;
	class[6].grade = 'Y';
	class[7].id = 3057;
	class[7].grade = 'F';
	
	
	TEST("IsEmpty", HTIsEmpty(ht), 1);
	TEST("Size", HTSize(ht), 0);
	
	/* insert */
	
	HTInsert(ht, class+0);
	
	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 1);
	
	HTInsert(ht, class+1);
	
	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 2);
	
	HTInsert(ht, class+2);
	
	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 3);
	
	HTInsert(ht, class+3);
	
	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 4);
	
	HTInsert(ht, class+4);
	
	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 5);
	
	HTInsert(ht, class+5);
	
	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 6);
	
	HTInsert(ht, class+6);
	
	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 7);
	
	HTInsert(ht, class+7);
	
	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 8);
	

	
	key_student.id = 1000;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student, NULL);
	
	key_student.id = 32;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 32);
	TESTC("Find", student->grade, 'B');
	
	key_student.id = 232;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student, NULL);
	
	key_student.id = 104701;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 104701);
	TESTC("Find", student->grade, 'C');
	
	key_student.id = 111;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 111);
	TESTC("Find", student->grade, 'E');
	

	
	key_student.id = 111;
	HTRemove(ht, &key_student);
	
	TEST("Size", HTSize(ht), 7);
	
	key_student.id = 1057;
	HTRemove(ht, &key_student);
	
	TEST("Size", HTSize(ht), 6);
	
	key_student.id = 2057;
	HTRemove(ht, &key_student);
	
	TEST("Size", HTSize(ht), 5);
	
	key_student.id = 1057;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student, NULL);
	
	key_student.id = 3057;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 3057);
	TESTC("Find", student->grade, 'F');
	
	key_student.id = 257;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 257);
	TESTC("Find", student->grade, 'A');
	
	
	
	status = HTForEach(ht, ActionIsFailed, NULL);
	printf("%d\n", status);
	TEST("ForEach", status, 1);

	key_student.id = 3057;
	HTRemove(ht, &key_student);
	
	status = HTForEach(ht, ActionIsFailed, NULL);
	TEST("ForEach", status, 0);
	

	
	status = HTForEach(ht, ActionLowerGrade, NULL);
	TEST("ForEach", status, 0);

	TESTC("ForEach", class[0].grade, 'B');
	TESTC("ForEach", class[1].grade, 'C');
	TESTC("ForEach", class[3].grade, 'D');
	TESTC("ForEach", class[4].grade, 'E');

	TESTC("ForEach", class[2].grade, 'E');
	TESTC("ForEach", class[5].grade, 'X');
	TESTC("ForEach", class[6].grade, 'Y');
	TESTC("ForEach", class[7].grade, 'F');
	

	
	new_grade = 'L';
	status = HTForEach(ht, ActionChangeGrade, &new_grade);
	TEST("ForEach", status, 0);

	TESTC("ForEach", class[0].grade, 'L');
	TESTC("ForEach", class[1].grade, 'L');
	TESTC("ForEach", class[3].grade, 'L');
	TESTC("ForEach", class[4].grade, 'L');
	
	TESTC("ForEach", class[2].grade, 'E');
	TESTC("ForEach", class[5].grade, 'X');
	TESTC("ForEach", class[6].grade, 'Y');
	TESTC("ForEach", class[7].grade, 'F');
	
	HTDestroy(ht);
	
	printf(BOLDBLUE "Completed Test1\n" DEF);
}
size_t HashSimple(const void *input)
{
	
	const char *str = input;
	size_t hash = (tolower(*str) - 97 + 6);
	
	/*printf("\nindex for: %s is: %ld\n",str,hash);*/
	
	return hash;
}

	
int CmpString(const void *key_1, const void *key_2)
{
	const char *str1 = key_1;
	const char *str2 = key_2;
	
	return !strcmp(str1, str2);
}
static hash_table_t *InitHashTable()
{
	hash_table_t *table = HTCreate(HashSimple, CmpString, NUM_LETTERS_IN_ABC - 1);

	char *buffer = NULL;
	
	FILE *fp = fopen(DICT_PATH , "r");
	
	/* feof() test the end of file indicator for the given string */
	while (feof(fp) == 0)
	{
		buffer = calloc(30, 1); /*?*/
		fgets(buffer, 30, fp);
		HTInsert(table, buffer);
	}
	
	fclose(fp);
	
	return table;
}

static int FreeData(void *data, void *arg)
{
	(void)(arg);
	free(data);
	return 0;
}	

/************************* main function *************************/

int main(void)
{

	TestCreateDestroy();
	Test1();
	PASS;
	/*int i = 0;
	int param = 0;
	
	char buffer[30];
	
	hash_table_t *table = InitHashTable();
	
	if(HTSize(table) != DICTIONARY_SIZE)
	{
		ERROR;
	}
	
	while(i < 5)
	{
		printf("Enter a word...\n");
		fgets(buffer, 30, stdin);
		
		if (HTFind(table, buffer) != NULL)
		{
			printf("Word found\n");
		}
		else
		{
			printf("Not found\n");
		}
		
		++i;
	}
	
	HTForEach(table, FreeData, &param);
	
	HTDestroy(table);
	
	return 0;*/
	

}




















