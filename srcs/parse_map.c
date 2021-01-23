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

//TODO:
// - rooms & links error management
// - map validation
// - display map with OpenGL
// - solving the map

#include <lem-in.h>

t_map 						*get_map(int fd)
{
	t_map 					*map;
	char 					*line;

	map = init_map();
	line = get_rooms(fd, map);
	if (!map->start)
		error(NO_START_ERR, map);
	if (!map->end)
		error(NO_END_ERR, map);
	get_links(line, fd, map);

	return map;
}
