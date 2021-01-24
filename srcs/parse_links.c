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

//TODO error management:
// - check for repeating links and reversed repeating links
// - simplify insert_link function

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

//TODO write validation function
// - check room1 and room2 vs link1 && link2
// - move this function to links_utils.c
// - write insertion algo
void 						validate_link(char *room1, char *room2, t_map *map)
{
	char 					*val1;
	char 					*val2;
	struct s_link_valid		*validator;
	struct s_link_valid		*next;

	printf("\nnot there yet cowboy hold ur horses\n\n");
	exit(0);

	validator = map->links_val;
	next = validator->next;
	while (next)
	{
		val1 = validator->link1;
		val2 = validator->link2;
		if (ft_strcmp(room1, val1) == 1)																				//link duplicate (a-b ; a-b)
		{
			if (ft_strcmp(room2, val2) == 1)
				error(DUPLICATE_LINK_ERR, map);
		}
		if (ft_strcmp(room1, val2) == 1)																				//reverse link duplicate (a-b ; b-a)
		{
			if (ft_strcmp(room2, val1))
				error(DUPLICATE_LINK_ERR, map);
		}
		validator = next;
		next = validator->next;
	}
	if (!validator)
	{
		validator = init_l_validator();
		validator->link1 = strdup(room1);
		validator->link2 = strdup(room2);
	}



//	printf("1: %s, 2: %s\n", validator->link1, validator->link2);
//	exit(0);
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

	validate_link(name1, name2, map);

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
	//exit(0);
	//---------------------------------------------------test stuff 2
}
