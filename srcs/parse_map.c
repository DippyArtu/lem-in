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
 * Map has following structure:
 * number_of_ants
 * the_rooms
 * the_links
*/

/*
 * Number of ants has to be a positive integer
 * There can't be 0 ants
 */

/* Room is defined by: *name* *coord_x* *coord_y* (i.e. room 1 14). Coordinates are always integers
 * Links between rooms are defined by: *name1*-*name2* (i.e. room1-room2)
 * Comments start with #
 * Lines starting with ## are commands modifying the properties of the line that comes right after
 * Unknown commands are ignored
 *
 * Room's name will never start with # or L
*/

//TODO read and parse rooms and links into the map
//TODO now do the process_room function
//TODO deal with errors in coordinate processing: empty lines, wrong coordinates, missing coordinates etc
//TODO after coordinates are up to speed — get rid of leaks

#include <lem-in.h>

void 						process_room(char *line, t_map *map, int flag)
{
	t_room_node 			*new_room;
	size_t					len;

	len = validate_room_name(line, map);
	new_room = init_room();
	new_room->room_name = strndup(line, --len);

	line += ++len;
	new_room->x = get_room_coordinate(&line, map);
	if (!line || *line != ' ')
		error(INVALID_COORD_ERR, map);
	line++;
	new_room->y = get_room_coordinate(&line, map);

	record_room(map, new_room, flag);
}

void 						process_comment(char *line, t_map *map, int fd)
{
	int 					err;

	err = 1;
	if (line[1] == '#')
	{
		if (ft_strcmp(line, "##start") == 1)
		{
			if (map->start)
				error(START_FLAG_ERR, map);
			if ((err = get_next_line(fd, &line)) == 1)
				process_room(line, map, START);
			free(line);
		}
		else if (ft_strcmp(line, "##end") == 1)
		{
			if (map->end)
				error(END_FLAG_ERR, map);
			if ((err = get_next_line(fd, &line)) == 1)
				process_room(line, map, END);
			free(line);
		}
	}
	if (err <= 0)
		error(FILE_READ_ERR, map);
}

void 						get_num_ants(int fd, t_map *map, char *line)
{
	if (get_next_line(fd, &line) != 1)
	{
		free(line);
		error(FILE_READ_ERR, map);
	}
	if ((!isdigit(line[0])) || (map->num_ants = ft_atoi(line)) <= 0)
	{
		free(line);
		error(ANT_NUM_ERR, map);
	}
	free(line);
}

//TODO error on empty & non-compliant line — empty line after ##start throws a sigfault
void 						read_map(int fd, t_map *map)
{
	char 					*line;
	int 					err;

	err = 0;
	line = NULL;
	get_num_ants(fd, map, line);
	while ((err = get_next_line(fd, &line)) == 1)
	{
		if (line[0] == '#')
			process_comment(line, map, fd);
		else if (isdigit(line[0]) || isalpha(line[0]))
			process_room(line, map, NONE);
		else
		{
			free(line);
			error(INVALID_LINE_ERR, map);
		}
		free(line);
	}
	free(line);
	if (err < 0)
		error(FILE_READ_ERR, map);
}

t_map 						*get_map(int fd)
{
	t_map 					*map;

	map = init_map();
	read_map(fd, map);

	return map;
}
