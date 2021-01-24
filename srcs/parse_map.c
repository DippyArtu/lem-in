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

/*
 * Links have to be directional:
 * i.e. given rooms 1 and 2, if the room 1 goes before room 2, the link should be as follows:
 * 1-2
 * a link of 2-1 will be considered an error
 */

//TODO:
// - rooms & links error management
// - map validation
// - display map with OpenGL

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
	if (map->coordinates)
	{
		ht_del_table(map->coordinates, RESIZE);
		free_room(map->dummy);
		map->coordinates = NULL;
	}

	get_links(line, fd, map);

	return map;
}
