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

struct s_links				*init_link(void)
{
	struct s_links			*link;

	if (!(link = (struct s_links *)malloc(sizeof(struct s_links))))
		error(MALLOC_FAIL_ERR, NULL);
	link->next = NULL;
	link->back = NULL;
	link->forward = NULL;
	return link;
}

t_map 						*init_map(void)
{
	t_map 					*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		error(MALLOC_FAIL_ERR, NULL);
	map->num_steps = 0;
	map->num_ants = 0;
	map->start = NULL;
	map->end = NULL;
//	map->rooms_head = NULL;
	map->rooms_hash = ht_new();
	return map;
}

t_room_node 				*init_room(void)
{
	t_room_node 			*room;

	if (!(room = (t_room_node *)malloc(sizeof(t_room_node))))
		error(MALLOC_FAIL_ERR, NULL);
	room->room_name = NULL;
	room->type = NONE;
	room->x = 0;
	room->y = 0;
	room->ant = NULL;
	room->room_next = NULL;
	room->links = NULL;
	return room;
}
