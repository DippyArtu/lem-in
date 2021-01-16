/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */


// Room is defined by: *name* *coord_x* *coord_y* (i.e. room 1 14). Coordinates are always integers
// Links between rooms are defined by: *name1*-*name2* (i.e. room1-room2)
// Comments start with #
// Lines starting with ## are commands modifying the properties of the line that comes right after
// Unknown commands are ignored

// room's name will never start with # or L

//TODO read and parse rooms and links into the map

#include <lem-in.h>

void 				process_line(t_map *map)
{
	map = NULL;
}

void 				read_map(int fd, t_map *map)
{
	char 			*line;

	if (get_next_line(fd, &line) != 1)
		error(FILE_READ_ERR, map);
	if (!isdigit(line[0]))
		error(ANT_NUM_ERR, map);
	map->num_ants = ft_atoi(line);

	while (get_next_line(fd, &line) == 1)
	{
		//printf("%s\n", line);

		process_line(map);
		free(line);
	}
	free(line);
}

t_map 				*get_map(int fd)
{
	t_map 			*map;

	map = init_map();
	read_map(fd, map);

	return map;
}
