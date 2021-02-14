/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

/*
 * Prereqs:
 * - OpenGL 3.2+
 * - GLFW
 * - GLEW
 * - CGLM | docs: https://cglm.readthedocs.io/en/latest/
 */

#include <lem-in.h>

//static void 						test(t_map *map);
void							points_test(t_map *map);

//TODO:
// - finish map stuff // - map validation ? mb do it on solving
// - visualize map
// - solve map
int							main(int argc, char **argv)
{
	t_map 					*map;
	int 					fd;

	fd = 0;
	map = NULL;

	if (argc < 2 || argc > 3)
		error(ARG_NUM_ERR, NULL);
	if (argc == 3 && (ft_strcmp(argv[2], "-t") != 1))
		error(ARG_NUM_ERR, NULL);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error(OPEN_FILE_ERR, NULL);

	if (argc == 2)
		map = init_map(GRAPHICS_ON);
	else if (argc == 3)
		map = init_map(GRAPHICS_OFF);

	get_map(fd, map);
	close(fd);

	//test(map);
	points_test(map);
	printf("rooms: %i\n", map->num_rooms);

	run_graphics(map);

	clean_up(map);

	return 0;
}

void						points_test(t_map *map)
{
	int 						i = 0;

	if (map->gl != NULL)
	{
		while (i < map->gl->num_points)
		{
			printf("%.3f	", map->gl->points[i]);
			i++;
			printf("%.3f\n", map->gl->points[i]);
			i++;
		}
		printf("x max:	%i		x min:	%i\n", map->gl->x_max, map->gl->x_min);
		printf("y max:	%i		y min:	%i\n", map->gl->y_max, map->gl->y_min);
		printf("\n");
	}
}

/*
static void 						test(t_map *map)
{
	//---------------------------------------------------test stuff 2
	struct s_links			*link;
	struct s_links			*l_next;
	struct s_room_node		*room;

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
	while (room && room->type != END)
	{
		printf("room name: %s\n", room->room_name);
		if (room->links)
		{
			l_next = room->links;
			while (l_next)
			{
				link = l_next;
				if (room->type == NONE)
				{
					if (link && link->back)
						printf("%s  --->  ", link->back->room_name);
					printf("%s --->  ", room->room_name);
					if (link && link->forward)
						printf("%s\n", link->forward->room_name);
				}
				else if (room->type == START)
				{
					printf("\nSTART: ");
					if (link && link->forward)
						printf("%s  --->  %s\n", room->room_name, link->forward->room_name);
				}
				else if (room->type == END)
				{
					if (link && link->back)
						printf("%s  --->  %s", link->back->room_name, room->room_name);
					printf(" : END\n");
				}
				printf("\n");
				l_next = l_next->next;
			}
		}
		else
		{
			printf("Room %s has no links\n\n", room->room_name);
			abort();
		}
		room = room->links->forward;
	}

	if (room && room->type == END)
	{
		printf("room name: %s\n", room->room_name);
		if (room->links)
		{
			l_next = room->links;
			while (l_next)
			{
				link = l_next;
				if (room->type == END)
				{
					if (link && link->back)
						printf("%s  --->  %s", link->back->room_name, room->room_name);
					printf(" : END\n");
				}
				printf("\n");
				l_next = l_next->next;
			}
		}
		else
		{
			printf("Room %s has no links\n\n", room->room_name);
			exit(1);
		}
	}
	else if (!room)
	{
		printf("Not the final room!\n\n"); // wrong links error
		exit(1);
	}
	printf("num ants: %i\n\n", map->num_ants);
	printf("\nStart room name: %s\n", map->start->room_name);
	printf("End room name: %s\n", map->end->room_name);
	//---------------------------------------------------test stuff 2
}
*/
