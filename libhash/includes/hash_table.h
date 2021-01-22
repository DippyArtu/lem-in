/* *********************************** */
/*                                     */
/*      LibHash project                */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#ifndef LEM_IN_HASH_TABLE_H
# define LEM_IN_HASH_TABLE_H

# include "prime.h"

# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define HT_INITIAL_BASE_SIZE 50																						// Initial size of the hash table

/*
 * Stores key-value pairs
 */
typedef struct 				s_hash_item
{
	char 					*key;
	char 					*value;
}							t_hash_item;

/*
 * Hash table stores an array of pointers to items as well as its size and how full it is
 */
typedef	struct 				s_hash_table
{
	int 					size;
	int 					base_size;
	int 					count;
	t_hash_item 			**items;
}							t_hash_table;

static t_hash_item 			HT_DELETED_ITEM = {NULL, NULL};												// Deleted item marker

t_hash_table 				*ht_new(void);																				// Creates a new hash table
void 						ht_del_table(t_hash_table *ht);																// Deletes hash table
void 						ht_insert(t_hash_table *ht, const char *key, const char *value);							// Inserts or updates the key-value pair into the table
char 						*ht_search(t_hash_table *ht, const char *key);												// Search for a key-value pair in the table
void 						ht_delete(t_hash_table *ht, const char *key);												// Delete the key-value pair from the table

#endif
