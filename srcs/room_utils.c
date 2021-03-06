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

size_t						validate_room_name(char *line, t_map *map)
{
	size_t 					len;

	len = 0;
	if (!line || line[0] == '\0' || line[0] == 'L' || line[0] == '#')
	{
		free(line);
		error(INVALID_ROOM_NAME_ERR, map);
	}
	while (line[len] != '\0')
	{
		if (line[len++] == ' ')
			break;
	}
	if (line[len] == '\0')
		return 0;
	return len;
}

int 						get_room_coordinate(char **line, t_map *map)
{
	char 					val[11];
	int 					i;
	int 					coord;

	i = 0;
	bzero(&val, 11);
	coord = 0;
	if (**line == '-')
	{
		val[i++] = **line;
		*line += 1;
	}
	while (**line && **line != ' ')
	{
		if (i >= 11 || **line < 48 || **line > 57)
			error(INVALID_COORD_ERR, map);
		val[i++] = **line;
		*line += 1;
	}
	coord = ft_atoi(val);
	return coord;
}

void 						record_room(t_map *map, t_room_node *new_room, int flag)
{
	if (flag == START)
	{
		new_room->type = START;
		map->start = new_room;
	}
	else if (flag == END)
	{
		new_room->type = END;
		map->end = new_room;
	}
	else if (flag == NONE)
		new_room->type = NONE;

	if (ht_search(map->rooms_hash, new_room->room_name) != NULL)
		error(DUPLICATE_NAME_ERR, map);
	ht_insert(map->rooms_hash, new_room->room_name, new_room);
}
