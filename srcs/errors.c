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

void 				error(int errno, t_map *map)
{
	if (errno == ARG_NUM_ERR)
	{
		printf(ARG_NUM);
		printf(USAGE);
	}
	else if (errno == OPEN_FILE_ERR)
		printf(OPEN_FILE);
	else if (errno == MALLOC_FAIL_ERR)
		printf(MALLOC_FAIL);
	else if (errno == FILE_READ_ERR)
		printf(FILE_READ);
	else if (errno == ANT_NUM_ERR)
		printf(ANT_NUM);
	clean_up(map);
	exit(1);
}
