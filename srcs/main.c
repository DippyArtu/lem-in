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
		error(ARG_NUM_ERR);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error(OPEN_FILE_ERR);

	//get map
	map = get_map(fd);
	close(fd);

	printf("\n\n%i\n", map->num_ants); // just a test

	clean_up(map);

	return 0;
}
