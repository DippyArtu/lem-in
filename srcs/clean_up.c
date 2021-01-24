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

	if (room && room->links)
	{
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
		room->links = NULL;
	}
}

void 						free_room(t_room_node *room)
{
	if (room)
	{
		if (room->room_name)
			free(room->room_name);
		if (room->ant)
			free(room->ant);
		if (room->links)
			free_links(room);
		free(room);
	}
	room = NULL;
}

void 						free_link_validator(struct s_link_valid *links)
{
	struct s_link_valid		*tmp;

	while (links)
	{
		tmp = links->next;
		if (links->link1)
			free(links->link1);
		if (links->link2)
			free(links->link2);
		free(links);
		links = tmp;
	}
	links = NULL;
}

void 						clean_up(t_map *map)
{
	if (map)
	{
		if (map->rooms_hash)
			ht_del_table(map->rooms_hash, FULL);
		if (map->coordinates)
		{
			printf("hi\n");
			ht_del_table(map->coordinates, RESIZE);
			free_room(map->dummy);
		}
		if (map->links_val)
			free_link_validator(map->links_val);
		free(map);
	}
}
