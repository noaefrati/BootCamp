/******************************************************************************* 
 * Description: Implemention of Hash Table                                     *
 * Author: Noa Efrati                                                          *
 * Reviewer: Ronny Efrrony                                                     *
 * Date: 04.01.2021                                                            *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/

#include <stdlib.h>      /* malloc, free, strtod                              */
#include <assert.h>      /* assert                                            */
#include "dlist.h"       /* dlist API                                         */
#include "hash_table.h"  /* hash_table API                                    */

#define FREE(x) free(x); x = NULL;

/************************* Structures and Typedefs ****************************/
   
typedef size_t (*hash_func_t)(const void *data);
typedef int (*match_func_t)(const void *one, const void *other);

struct hash_table
{
	dllist_t **table;
    hash_func_t hash_func;
    match_func_t match_func;
    size_t table_size;
};

/******************************************************************************/
/***                     Private function declarations                      ***/
/******************************************************************************/

static hash_table_t *AllocateLists(hash_table_t *ht);
static size_t GetKey(const hash_table_t *table, const void *data);

/******************************************************************************/
/******************************************************************************/
                                                         
/**************************** Create and Destroy ******************************/


/*
 * Time Complexity: worst O(table_size)  
 */
hash_table_t *HTCreate(size_t (*hash_func_t)(const void *data),
                       int (*match_func_t)(const void *one, const void *other),
                       size_t table_size)

{
	hash_table_t *hash_table = NULL;

	assert(hash_func_t);
	
	hash_table = (hash_table_t *) malloc(sizeof(hash_table_t));
	
	if (NULL != hash_table)
	{
		hash_table->table = malloc(sizeof(dllist_t *) * table_size);
		
		if (NULL != hash_table->table)
		{
			hash_table->hash_func = hash_func_t;
			hash_table->table_size = table_size;
			hash_table->match_func = match_func_t;
			
			hash_table = AllocateLists(hash_table);
		}
		else
		{
			FREE(hash_table);
		}
	}
	
	return hash_table;	
}

/*
 * Description: Destroy a given hash table, removing all of its elements.
 * Return nothing
 * Time Complexity: O(n + table_size)
 */
void HTDestroy(hash_table_t *table)
{
	size_t i = 0;
	
	assert(table);
	
	for (i = 0; table->table_size > i; ++i)
	{
		DLLDestroy(table->table[i]);
		table->table[i] = NULL;
	}
	
	FREE(table->table);
	FREE(table);
}

/***************************** Insert and Remove ******************************/

/*
 * Time Complexity: O(1)
 */
int HTInsert(hash_table_t *table, const void *data)
{
	size_t key = 0;
	dllist_t *list = NULL;
	dllist_iter_t push_front_iter = {NULL};
	
	assert(table);
	
	key = GetKey(table, data);
	list = table->table[key];
	push_front_iter = DLLPushFront(list, data);
	
	return (DLLIsSameIter(push_front_iter, DLLEnd(list)));
}

/*
 * Time Complexity: average O(1) worst O(n)
 */
void HTRemove(hash_table_t *table, const void *data)
{
	dllist_iter_t iter = {NULL};
	dllist_t *list = NULL;
	size_t key = 0;
	
	assert(table);

	
	key = GetKey(table, data);
	list = table->table[key];
	
	iter = DLLFind(DLLBegin(list), DLLEnd(list), data, table->match_func);
	
	if (!DLLIsSameIter(iter, DLLEnd(list)))
	{
		DLLRemove(iter);
	}
}

/****************************** Basic Utility *********************************/

/*
 * Description: Get the total number of elements in the hash table.
 * Return size (which is 0 if there are no elements).
 * Time Complexity: O(n + table_size) 
 */
size_t HTSize(const hash_table_t *table)
{
	size_t size = 0;
	size_t i = 0;
	
	assert(table);
	
	for (; i < table->table_size; ++i)
	{
		size += DLLSize(table->table[i]);
	}
	
	return size;
}

/*
 * Description: Check whether given hash table has no elements.
 * Return 1 is table is empty, 0 otherwise.
 * Time Complexity: O(table_size)
 */
int HTIsEmpty(const hash_table_t *table)
{
	size_t index = 0;
	int ret_val = 1;
	
    assert(table);

    for(; index < table->table_size && (0 != ret_val); ++index)
    {
        ret_val = DLLIsEmpty(table->table[index]);    
    }
   
    return ret_val;
}

/*
 * Time Complexity: Worst: O(n), Average: O(1)
 */
void *HTFind(const hash_table_t *table, const void *value)
{
	size_t key = 0;
	dllist_t *list = NULL;
	dllist_iter_t found_iter = NULL;
	
	assert(table);
	assert(value);
	
	key = GetKey(table, value);
	list = table->table[key];
	
	found_iter = DLLFind(DLLBegin(list), 
						DLLEnd(list),
						value,
						table->match_func);
	
	return DLLGetData(found_iter);
}

/*
 * Time Complexity: O(n)
 */
int HTForEach(const hash_table_t *table,
              int (action_func)(void *data, void *params),
              void *params)
{
	dllist_t *list = NULL;
	size_t i = 0;
	int action_status = 0;
	
	assert(table);
	assert(action_func);
	
	for (i = 0; table->table_size > i && (0 == action_status); ++i)
	{
		list = table->table[i];
		action_status = DLLForEach(DLLBegin(list), DLLEnd(list),
							                         action_func, params);				                         
	}
	
	return action_status;
}
/********************************** Advanced **********************************/
/*
 * Description: Returns the current load factor of the hash table (average 
 * number of elements in the hash table per bucket).
 * Return value: current load factor.
 * Time Complexity: O(n + table_size)
 */
double HTLoadFactor(const hash_table_t *ht);
/*
 * Description: Returns the current standard deviation of the hash table.
 * Return value: standard deviation of current hash table.
 * Time Complexity: O(n + table_size)
 */
double HTStandardDeviation(const hash_table_t *ht);
/******************************************************************************/

static size_t GetKey(const hash_table_t *table, const void *data)
{
	assert(table);
	assert(data);
	
	return (table->hash_func((void *)data) % table->table_size);
}

static hash_table_t *AllocateLists(hash_table_t *ht)
{
	size_t key = 0;
	
	assert(ht);
			
	for (; ht->table_size > key; ++key)
	{
		ht->table[key] = DLLCreate();
		if (NULL == ht->table[key])
		{
			ht->table_size = key;
			HTDestroy(ht);
			return NULL;	
		}
	}
	
	return ht;
}


