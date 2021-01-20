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
