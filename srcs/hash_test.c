/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#include <lem-in.h>

void 						test_hash(void)
{
	printf("hi hash\n\n");

	t_hash_table 			*ht;

	ht = ht_new();

	ht_insert(ht, "abc", "123");
	ht_insert(ht, "efg", "456");

	printf("key abc: %s\n", ht_search(ht, "abc"));
	printf("key efg: %s\n", ht_search(ht, "efg"));
	if (ht_search(ht, "abc") != NULL)
		printf("key abc already in use\n");
	if (ht_search(ht, "no_value") == NULL)
		printf("key no_value is not in use\n");

	ht_del_table(ht);
	printf("done\n");
}
