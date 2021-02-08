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

void 						insert_link(struct s_room_node *room_curr, struct s_room_node *room_insert, int flag)
{
	struct s_links			*l_next;
	struct s_links			*l_head;
	struct s_links			*link;
	struct s_room_node		*prev_room_joined;

	l_next = NULL;
	link = NULL;
	prev_room_joined = NULL;
	l_head = room_curr->links;
	if (room_curr->links)
	{
		if ((room_curr->type == START) && flag == FORWARD_LINK && !room_curr->links->forward)
		{
			room_curr->links->forward = room_insert;
			return;
		}
		if ((room_curr->type == END) && flag == BACKWARD_LINK && !room_curr->links->back)
		{
			room_curr->links->back = room_insert;
			return;
		}
		if ((room_curr->type == NONE) && (!room_curr->links->forward || !room_curr->links->back))
		{
			if (flag == FORWARD_LINK)
				room_curr->links->forward = room_insert;
			else if (flag == BACKWARD_LINK)
				room_curr->links->back = room_insert;
			return;
		}
		if (room_curr->type != START)
			prev_room_joined = l_head->back;
		link = l_head;
		l_next = l_head->next;
		while (l_next != NULL)
		{
			link = l_next;
			l_next = l_next->next;
		}
	}
	l_next = init_link();
	if (flag == FORWARD_LINK)
	{
		l_next->forward = room_insert;
		if (l_head != NULL && l_next->back == NULL)
			l_next->back = prev_room_joined;
	}
	else if (flag == BACKWARD_LINK)
		l_next->back = room_insert;
	if (l_head != NULL)
	{
		link->next = l_next;
		room_curr->links = l_head;
	}
	else if (l_head == NULL)
		room_curr->links = l_next;
}

void 						create_link(t_map *map, char *name1, char *name2, t_hash_table *room_points_ht)
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

	if (room_points_ht != NULL)
	{
		gl_insert_points(map, room1, room_points_ht);
		gl_insert_points(map, room2, room_points_ht);
	}
}

void 						process_link(char *line, t_map *map, t_hash_table *room_points_ht)
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
	validate_link(name1, name2, map);
	create_link(map, name1, name2, room_points_ht);
	free(name1);
	free(name2);
}

void 						get_links(char *line, int fd, t_map *map)
{
	int 					err;
	t_hash_table 			*room_points_ht;

	err = 0;
	room_points_ht = NULL;

	if (map->gl != NULL)
	{
		gl_init_points(map);
		room_points_ht = ht_new();
	}

	process_link(line, map, room_points_ht);
	while ((err = get_next_line(fd, &line)) == 1)
		process_link(line, map, room_points_ht);
	free(line);
	if (err < 0)
		error(FILE_READ_ERR, map);
	free_link_validator(map->links_val);
	map->links_val = NULL;

	ht_del_table(room_points_ht, RESIZE);
}
