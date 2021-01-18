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

t_map 						*init_map(void)
{
	t_map 					*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		error(MALLOC_FAIL_ERR, NULL);
	map->num_steps = 0;
	map->num_ants = 0;
	map->start = NULL;
	map->end = NULL;
	map->rooms_head = NULL;
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
	room->t_links = NULL;
	return room;
}
