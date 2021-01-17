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

size_t				validate_room_name(char *line, t_map *map)
{
	size_t 			len;

	len = 0;
	if (line[0] == 'L')
	{
		free(line);
		error(INVALID_ROOM_NAME_ERR, map);
	}
	while (line[len++] != ' ')
		;
	if (!line[len])
	{
		free(line);
		error(INVALID_ROOM_NAME_ERR, map);
	}
	return len;
}

//TODO throw an error on non-numbers
int 				get_room_coordinate(char **line, t_map *map, size_t len)
{
	char 			val[11];
	int 			i;
	int 			coord;

	i = 0;
	bzero(&val, 11);
	coord = 0;
	*line += len;
	while (**line && **line != ' ')
	{
		if (i >= 11)
			error(INVALID_COORD_ERR, map);
		val[i++] = **line;
		*line += 1;
	}
	coord = ft_atoi(val);
	return coord;
}
