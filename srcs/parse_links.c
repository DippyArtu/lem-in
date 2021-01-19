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

void 						get_links(char *line, int fd, t_map *map)
{
//	struct s_room_node		*room;
	char 					*name1;
	char 					*name2;
	fd = 1;

	name1 = get_link_name(&line, map);
	if (*line == '\0')
		error(INVALID_LINK_ERR, map);
	line++;
	name2 = get_link_name(&line, map);

	//----------------------------------------- test stuff
	printf("name1: %s\n", name1);
	printf("name2: %s\n", name2);
	exit(0);
	//----------------------------------------- test stuff

	free(name1);
	free(name2);
}
