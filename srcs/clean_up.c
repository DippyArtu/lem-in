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

//TODO links clean-up
struct s_room_node 			*free_room(t_room_node *room)
{
	struct s_room_node		*next;

	if (room->room_name)
		free(room->room_name);
	if (room->ant)
		free(room->ant);
	next = room->room_next;
	free(room);
	return next;
}

void 						clean_up(t_map *map)
{
	struct s_room_node		*tmp;
	struct s_room_node		*next;

	tmp = map->rooms_head;
	next = NULL;
	if (map->rooms_head)
	{
		while (1)
		{
			next = free_room(tmp);
			if (!next)
				break;
			tmp = next;
		}
	}
	if (map)
		free(map);
}
