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

//TODO build the links
// - existing links are getting lost instead of being updated

//TODO after links are done do:
// - error management
// - make sure there aren't leaks


//TODO work on the link insertion algorithm
// - what i think happens here, is that when there is a link existing in a room (forward or backward)
//	 instead of inserting a missing link, it inserts a new link node
//   i.e. the room has a fov link but no back, instead of writing in a back link, it creates a new link node just for the back link alone
//	 so the solution would be to check if theres a missing link in a node and if it makes sense to update the missing link before
//	 inserting a new node
void 						insert_link(struct s_room_node *room_curr, struct s_room_node *room_insert, int flag)
{
	struct s_links			*links_room;
	struct s_links			*tmp;

	tmp = NULL;
	links_room = init_link();

	if (room_curr->links)
	{
		tmp = room_curr->links;
		while (room_curr->links->next)
			room_curr->links = room_curr->links->next;
	}
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
	if (!(room1 = find_room(map, name1)) || !(room2 = find_room(map, name2)))
	{
		free(name1);
		free(name2);
		error(NO_LINK_ROOM_ERR, map);
	}

	insert_link(room1, room2, FORWARD_LINK);
	insert_link(room2, room1, BACKWARD_LINK);

	//TODO not the best way to display the links — rooms with multiple links are ignored
	// - might as well code it in properly coz i'll need to use it later on anyways
	//---------------------------------------------------test stuff
	printf("%s	to	", room1->room_name);
	if (room1->links->forward)
		printf("%s\n", room1->links->forward->room_name);

	printf("%s	to	", room2->room_name);
	if (room2->links->back)
		printf("%s\n\n", room2->links->back->room_name);
	//---------------------------------------------------test stuff
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
	exit(0);
}
