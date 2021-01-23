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

#define FORWARD_LINK 0
#define BACKWARD_LINK 1

//TODO after links are done do:
// - error management
// - make sure there aren't leaks

void 						insert_link(struct s_room_node *room_curr, struct s_room_node *room_insert, int flag)
{
	struct s_links			*links_room;
	struct s_links			*tmp;

	tmp = NULL;
	links_room = NULL;

	if (room_curr->links)
	{
		if (flag == FORWARD_LINK && !room_curr->links->forward && (room_curr->type != END))
		{
			room_curr->links->forward = room_insert;
			return;
		}
		if (flag == BACKWARD_LINK && !room_curr->links->back && (room_curr->type != START))
		{
			room_curr->links->back = room_insert;
			return;
		}
		tmp = room_curr->links;
		while (room_curr->links->next)
			room_curr->links = room_curr->links->next;
	}
	links_room = init_link();
	room_curr->links = links_room;
	if (flag == FORWARD_LINK)
		links_room->forward = room_insert;
	else if (flag == BACKWARD_LINK)
		links_room->back = room_insert;
	if (tmp)
		room_curr->links = tmp;
	else
		room_curr->links = links_room;
	tmp = NULL;
}

void 						create_link(t_map *map, char *name1, char *name2)
{
	struct s_room_node		*room1;
	struct s_room_node		*room2;

	room1 = NULL;
	room2 = NULL;

	if (!(room1 = ht_search(map->rooms_hash, name1)) || !(room2 = ht_search(map->rooms_hash, name2)))
	{
		free(name1);
		free(name2);
		error(NO_LINK_ROOM_ERR, map);
	}

	insert_link(room1, room2, FORWARD_LINK);
	insert_link(room2, room1, BACKWARD_LINK);
}

void 						process_link(char *line, t_map *map)
{
	char 					*name1;
	char 					*name2;
	char 					*line_tmp;

	line_tmp = line;
	name1 = get_link_name(&line, map);
	if (*line == '\0')
		error(INVALID_LINK_ERR, map);
	line++;
	name2 = get_link_name(&line, map);
	free(line_tmp);

	create_link(map, name1, name2);

	free(name1);
	free(name2);
}

void 						get_links(char *line, int fd, t_map *map)
{
	int 					err;

	err = 0;
	process_link(line, map);
	while ((err = get_next_line(fd, &line)) == 1)
	{
		process_link(line, map);
	}
	free(line);
	if (err < 0)
		error(FILE_READ_ERR, map);


	//---------------------------------------------------test stuff 2
	int 					i_rooms;
	int 					i_links;
	struct s_links			*link;
	struct s_links			*l_next;
	struct s_room_node		*room;

	i_links = 0;
	i_rooms = 0;

	if (!map->start)
	{
		printf("No start room\n");
		abort();
	}
	if (!map->end)
	{
		printf("No end room\n");
		abort();
	}

	room = map->start;
	while (room->type != END)
	{
		printf("room name: %s\n", room->room_name);
		if (room->links)
		{
			l_next = room->links;
			while (l_next)
			{
				i_links++;
				link = l_next;
				if (room->type == NONE)
				{
					printf("%s  --->  %s --->  %s\n", link->back->room_name, room->room_name, link->forward->room_name);
				}
				else if (room->type == START)
				{
					printf("\nSTART: ");
					printf("%s  --->  %s\n", room->room_name, link->forward->room_name);
					printf("________________________\n");
				}
				else if (room->type == END)
				{
					printf("________________________\n");
					printf("%s  --->  %s", link->back->room_name, room->room_name);
					printf(" : END\n");
				}
				printf("\n");
				l_next = link->next;
			}
		}
		else
			printf("Room %s has no links\n\n", room->room_name);
		room = room->links->forward;
		i_rooms++;
	}
	printf("%i rooms displayed\n", i_rooms);
	printf("%i links displayed\n\n", i_links);
	//exit(0);
	//---------------------------------------------------test stuff 2
}
