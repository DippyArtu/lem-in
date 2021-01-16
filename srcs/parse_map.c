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

//TODO read and parse the map

#include <lem-in.h>

void 				read_map(int fd, t_map *map)
{
	char 			*line;
	map->num_ants = 1; // for test only

	while (get_next_line(fd, &line) == 1)
	{
		printf("%s\n", line);
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
