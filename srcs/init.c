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

t_map 				*init_map(void)
{
	t_map 			*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		error(MALLOC_FAIL_ERR, NULL);
	map->num_steps = 0;
	map->num_ants = 0;
	map->start = NULL;
	map->end = NULL;
	return map;
}
