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

char 						*get_link_name(char **line, t_map *map)
{
	char 					*name;
	int 					i;

	if (!line || **line == '\0')
		error(INVALID_LINE_ERR, map);
	if (!(name = (char *)malloc(101 * sizeof(char))))
		error(MALLOC_FAIL_ERR, map);
	bzero(name, 101);
	i = 0;

	while (**line != '\0' && **line != '-')
	{
		if (i == 100)
			error(LARGE_NAME_ERR, map);
		name[i++] = **line;
		*line += 1;
	}
	return name;
}

struct s_room_node			*find_room(t_map *map, char *name)
{
	struct s_room_node		*room;

	room = map->rooms_head;
	while (room)
	{
		if (ft_strcmp(name, room->room_name) == 1)
			return room;
		room = room->room_next;
	}
	return NULL;
}
