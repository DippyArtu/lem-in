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

void 						free_links(t_room_node *room)
{
	struct s_links			*next;
	struct s_links			*links;

	links = room->links;
	while (links)
	{
		links->back = NULL;
		links->forward = NULL;
		next = links->next;
		free(links);
		links = next;
	}
	free(links);
}

void 						free_room(t_room_node *room)
{
	if (room->room_name)
		free(room->room_name);
	if (room->ant)
		free(room->ant);
	if (room->links)
		free_links(room);
	free(room);
}

void 						clean_up(t_map *map)
{
	if (map)
	{
		if (map->rooms_hash)
			ht_del_table(map->rooms_hash, FULL);
		free(map);
	}
}
