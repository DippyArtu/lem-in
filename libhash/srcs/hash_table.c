/* *********************************** */
/*                                     */
/*      LibHash project                */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#include <hash_table.h>

//-------------------//
// SERVICE FUNCTIONS //
//-------------------//

// Creates a new hash item
static t_hash_item 			*ht_new_item(const char *key, t_room_node *value)
{
	t_hash_item 			*h_item;

	if (!(h_item = (t_hash_item *)malloc(sizeof(t_hash_item))))
	{
		printf("\nHASH TABLE MALLOC ERROR @ ht_new_item\n");
		abort();
	}
	h_item->key = strdup(key);
	h_item->value = value;
	return h_item;
}

static t_hash_table			*ht_new_sized(const int base_size)
{
	t_hash_table 			*ht;

	if (!(ht = (t_hash_table *)malloc(sizeof(t_hash_table))))
	{
		printf("\nHASH TABLE MALLOC ERROR @ ht_new_sized\n");
		abort();
	}
	ht->base_size = base_size;
	ht->size = next_prime(ht->base_size);
	ht->count = 0;
	if (!(ht->items = calloc((size_t)ht->size, sizeof(t_hash_item *))))
	{
		printf("\nHASH TABLE CALLOC ERROR @ ht_new_sized\n");
		abort();
	}
	return ht;
}

t_hash_table 				*ht_new(void)
{
	return ht_new_sized(HT_INITIAL_BASE_SIZE);
}


struct s_room_node 			*free_room(t_room_node *room);
void 						free_links(t_room_node *room);
// Deletes hash item
static void 				ht_del_item(t_hash_item *item, int flag)
{
	free(item->key);
	if (flag == FULL)
		free_room(item->value);
	else if (flag == RESIZE)
		item->value = NULL;
	free(item);
}

void 						ht_del_table(t_hash_table *ht, int flag)
{
	int 					i;
	t_hash_item 			*item;

	item = NULL;
	i = 0;
	while (i < ht->size)
	{
		item = ht->items[i];
		if (item != NULL)
			ht_del_item(item, flag);
		i++;
	}
	free(ht->items);
	free(ht);
}

/*
 * Generic string hashing algorithm:
 * - Input string is converted into a large integer
 * - Result is reduced to the integer in a fixed range by taking it's remainder mod pool_size (size of the hash table)
 * - Variable num is a prime number larger than the size of the alphabet (in this case, ASCII, which has 128 symbols)
 * - Different values of num will output different results of the hash function
 */
static int 					ht_hash(const char *str, const int num, const int pool_size)
{
	long 					hash;
	int 					len_str;
	int 					i;

	i = 0;
	hash = 0;
	len_str = (int)strlen(str);
	while (i < len_str)
	{
		hash += (long)pow(num, len_str - (i + 1)) * str[i];
		hash = hash % pool_size;
		i++;
	}
	return (int)hash;
}

/*
 * Collision resolution method using open addressing with double hashing:
 * - attempt is a number of collisions for a particular hash, incremented if a collision for the slot occurred
 *
 * - if no collisions occurred for a slot, attempt = 0, meaning a resultant hash will be just hash_a
 * - to avoid a situation where hash_b returns 0, thus reducing second term to 0, 1 is added to the result of the second
 *  hash, making sure the result is never 0
 * - the result is a combination of hash_a and hash_b
 */
static int 					ht_get_hash(const char *str, const int pool_size, const int attempt)
{
	int 					hash_a;
	int 					hash_b;
	int 					result;

	hash_a = ht_hash(str, HT_PRIME_1, pool_size);
	hash_b = ht_hash(str, HT_PRIME_2, pool_size);
	result = (hash_a + (attempt * (hash_b + 1))) % pool_size;
	return result;
}

/*
 * Resize function:
 * - Makes sure we aren't attempting to reduce the size of the table below minimum
 * - All items are inserted into the new hashtable, the old one is deleted
 */
static void 				ht_resize(t_hash_table *ht, const int base_size)
{
	t_hash_table 			*new_ht;
	t_hash_item 			*item;
	t_hash_item 			**tmp_items;
	int 					i;
	int 					tmp_size;

	if (base_size < HT_INITIAL_BASE_SIZE)
		return;
	i = 0;
	new_ht = ht_new_sized(base_size);
	while (i < ht->size)
	{
		item = ht->items[i];
		if (item != NULL && item != &HT_DELETED_ITEM)
			ht_insert(new_ht, item->key, item->value);
		i++;
	}

	ht->base_size = new_ht->base_size;
	ht->count = new_ht->count;

	tmp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = tmp_size;

	tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;

	ht_del_table(new_ht, RESIZE);
}

// Increase the size of the hash table
static void 				ht_resize_up(t_hash_table *ht)
{
	int 					new_size;

	new_size = ht->base_size * 2;
	ht_resize(ht, new_size);
}

// Decrease the size of the hash table
static void 				ht_resize_down(t_hash_table *ht)
{
	int 					new_size;

	new_size = ht->base_size / 2;
	ht_resize(ht, new_size);
}



//---------------//
// API FUNCTIONS //
//---------------//

/*
 * Insert the key-value pair into the table:
 * - Iterate through indexes to find an empty slot to find next empty slot
 * - Insert the pair into the slot and increment the count variable to indicate a new pair has been added
 * - If the load of the table is above 70%, the size of the table is increased
 */
void 						ht_insert(t_hash_table *ht, const char *key, t_room_node *value)
{
	t_hash_item 			*item;
	t_hash_item 			*cur_item;
	int 					index;
	int 					i;
	int 					load;

	load = ht->count * 100 / ht->size;
	if (load > 70)
		ht_resize_up(ht);
	i = 1;
	item = ht_new_item(key, value);
	index = ht_get_hash(item->key, ht->size, 0);
	cur_item = ht->items[index];
	while (cur_item != NULL)
	{
		if (cur_item != &HT_DELETED_ITEM)
		{
			if (strcmp(cur_item->key, key) == 0)
			{
				ht_del_item(cur_item, FULL);
				ht->items[index] = item;
				return;
			}
		}
		index = ht_get_hash(item->key, ht->size, i);
		cur_item = ht->items[index];
		i++;
	}
	ht->items[index] = item;
	ht->count++;
}

/*
 * Searching for the key in the hash table:
 * - Check whether the item's key matches the search key
 * - If it does, return the item's value
 * - If doesn't, return NULL to indicate the the absence of such item
 */
t_room_node					*ht_search(t_hash_table *ht, const char *key)
{
	int 					index;
	int 					i;
	t_hash_item 			*item;

	index = ht_get_hash(key, ht->size, 0);
	item = ht->items[index];
	i = 1;
	while (item != NULL)
	{
		if (item != &HT_DELETED_ITEM)
		{
			if (strcmp(item->key, key) == 0)
				return item->value;
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	return NULL;
}

/*
 * Deleting a key-value pair from the table:
 * - The item to be deleted may be a part of the collision chain
 * - Instead of deleting the item (which will break the chain), the item is marked with a pointer to a global watch item, representing a deleted item
 * - The count variable is then decremented
 * - If the load of the table is below 10%, the size of the table is decreased
 */
void 						ht_delete(t_hash_table *ht, const char *key)
{
	int 					index;
	int 					i;
	t_hash_item 			*item;
	int 					load;

	load = ht->count * 100 / ht->size;
	if (load < 10)
		ht_resize_down(ht);
	i = 1;
	index = ht_get_hash(key, ht->size, 0);
	item = ht->items[index];
	while (item != NULL)
	{
		if (item != &HT_DELETED_ITEM)
		{
			if (strcmp(item->key, key) == 0)
			{
				ht_del_item(item, FULL);
				ht->items[index] = &HT_DELETED_ITEM;
			}
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	ht->count--;
}
