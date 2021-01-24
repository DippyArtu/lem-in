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

//TODO:
// - finish map stuff
// - solve map

int							main(int argc, char **argv)
{
	t_map 					*map;
	int 					fd;

	fd = 0;
	map = NULL;

	if (argc != 2)
		error(ARG_NUM_ERR, NULL);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error(OPEN_FILE_ERR, NULL);

	//get map
	map = get_map(fd);
	close(fd);

	//---------------------------------------------- test stuff
	printf("num ants: %i\n\n", map->num_ants);
	printf("\nStart room name: %s\n", map->start->room_name);
	printf("End room name: %s\n", map->end->room_name);
	//----------------------------------------------

	clean_up(map);

	return 0;
}
