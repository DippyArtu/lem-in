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

//TODO make sure that rooms received do exist and build the links

//void 						create_link(t_map *map, char *name1, char *name2)
//{
//
//}

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

	printf("name1: %s	name2: %s\n", name1, name2);
	//validate and build a link here

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
}
