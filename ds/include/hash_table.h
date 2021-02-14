#ifndef __OL_97__HASH_TABLE_H__
#define __OL_97__HASH_TABLE_H__

/******************************************************************************
 * Description: API For Hash Table                                            *
 *                                                                            *
 * Infinity Labs - OL97                                                       *
 ******************************************************************************/

#include <stddef.h> /* size_t */

/************************* Structures and Typedefs ****************************/

typedef struct hash_table hash_table_t;


/*    
	typedef size_t (*hash_func_t)(const void *data);
	typedef int (*match_func_t)(const void *one, const void *other);

    struct hash_table
    {
        dllist_t **table;
        hash_func_t hash_func;
        match_func_t match_func;
        size_t table_size;
    }
*/

/***                                                                        ***/
/******************************** Functions ***********************************/
/***                                                                        ***/

/**************************** Create and Destroy ******************************/

/*
 * Description: Create a new, empty hash table with two functions.
 * hash_func is used for generating a desired key from data items. hash 
 * function should provide a hash code that is as unique and uniformly 
 * distributed as possible to ensure meeting stated complexities.
 * Bucketing is then done by the generated key.
 * The is_match function is used to uniquely identify an element in case of 
 * collisions. match_func return 1 for an exact match, 0 otherwise.
 * HTCreate returns pointer to newly created table,
 * or NULL if memory allocation failed.
 * Time Complexity: worst O(table_size)  
 */
hash_table_t *HTCreate(size_t (*hash_func)(const void *data),
                       int (*match_func)(const void *one, const void *other),
                       size_t table_size);

/*
 * Description: Destroy a given hash table, removing all of its elements.
 * Return nothing
 * Time Complexity: O(n + table_size)
 */
void HTDestroy(hash_table_t *ht);

/***************************** Insert and Remove ******************************/

/*
 * Description: Insert a new value into given hash table.
 * Value is matched a key using the user's hash_func.
 * Return 0 if placement was successful, 1 otherwise.
 * Placement may be unsuccessful if memory allocation fails.
 * Time Complexity: O(1)
 */
int HTInsert(hash_table_t *ht, const void *data);

/*
 * Description: Remove data from given hash table, if exists.
 * Data is hashed using the user's hash_func.
 * In case of collisions, data is further matched using the user's match_func.
 * Return value: None.
 * Time Complexity: average O(1) worst O(n)
 */
void HTRemove(hash_table_t *ht, const void *data);

/****************************** Basic Utility *********************************/

/*
 * Description: Get the total number of elements in the hash table.
 * Return size (which is 0 if there are no elements).
 * Time Complexity: O(n + table_size) 
 */
size_t HTSize(const hash_table_t *ht);

/*
 * Description: Check whether given hash table has no elements.
 * Return 1 is table is empty, 0 otherwise.
 * Time Complexity: O(table_size)
 */
int HTIsEmpty(const hash_table_t *ht);

/*
 * Description: Find a specific value in the hash table.
 * Bucket for value is found using the user's hash_func.
 * In case of collisions, further searching in the correct bucket is done using
 * the user's match_func.
 * Return pointer to data value found, or NULL if value does not exist.
 * Time Complexity: Worst: O(n), Average: O(1)
 */
void *HTFind(const hash_table_t *ht, const void *value);

/*
 * Description: Perform an action on every value in given hash table.
 * action_func resutns 0 upon success. If action_func ever returns a non-zero
 * value, HTForEach stop immediately.
 * Return 0 upon success, 1 otherwise.
 * Pay attention! If the data by which an element is sorted/hashed is changed 
 * the value may not be reached !
 * Time Complexity: O(n)
 */
int HTForEach(const hash_table_t *ht,
              int (*action_func)(void *data, void *params),
              void *params);

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

#endif /* __OL_97__HASH_TABLE_H__ */
