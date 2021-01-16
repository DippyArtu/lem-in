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

int					main(int argc, char **argv)
{
	t_map 			*map;
	int 			fd;

	fd = 0;
	map = NULL;

	if (argc != 2)
		error(ARG_NUM_ERR, NULL);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error(OPEN_FILE_ERR, NULL);

	//get map
	map = get_map(fd);
	close(fd);

	printf("num ants: %i\n", map->num_ants);

	clean_up(map);

	return 0;
}
