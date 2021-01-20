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

//TODO build the links
// - yeah sig fault lol

//TODO after links are done do:
// - error management
// - make sure there aren't leaks

void 						create_link(t_map *map, char *name1, char *name2)
{
	struct s_room_node		*room1;
	struct s_room_node		*room2;
	struct s_links			*links_room1;
	struct s_links			*links_room2;
	struct s_links			*tmp;

	room1 = NULL;
	room2 = NULL;
	tmp = NULL;
	if (!(room1 = find_room(map, name1)) || !(room2 = find_room(map, name2)))
	{
		free(name1);
		free(name2);
		error(NO_LINK_ROOM_ERR, map);
	}

	links_room1 = init_link();
	links_room2 = init_link();

	if (room1->links)
	{
		tmp = room1->links;
		while (room1->links->next)
			room1->links = room1->links->next;
	}
	room1->links = links_room1;
	links_room1->forward = room2;
	if (tmp)
		room1->links = tmp;
	else
		room1->links = links_room1;

	tmp = NULL;
	if (room2->links)
	{
		tmp = room2->links;
		while (room2->links->next)
			room2->links = room2->links->next;
	}
	room2->links = links_room2;
	links_room2->back = room1;
	if (tmp)
		room2->links = tmp;
	else
		room2->links = links_room2;
	tmp = NULL;

	printf("%s	to	%s\n", room1->room_name, room1->links->forward->room_name);
	printf("%s	to	%s\n\n", room2->room_name, room2->links->back->room_name);
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

//TODO sigfault fucks on second entry to process_link function

void 						get_links(char *line, int fd, t_map *map)
{
	int 					err;

	err = 0;
	process_link(line, map);
	while ((err = get_next_line(fd, &line)) == 1)
	{
		printf("hi\n");
		process_link(line, map);
	}
	free(line);
	if (err < 0)
		error(FILE_READ_ERR, map);
}
