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

void 						error(int errno, t_map *map)
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
	else if (errno == INVALID_LINE_ERR)
		printf(INVALID_LINE);
	else if (errno == INVALID_ROOM_NAME_ERR)
		printf(INVALID_ROOM_NAME);
	else if (errno == INVALID_COORD_ERR)
		printf(INVALID_COORD);
	else if (errno == START_FLAG_ERR)
		printf(START_FLAG);
	else if (errno == END_FLAG_ERR)
		printf(END_FLAG);
	else if (errno == NO_START_ERR)
		printf(NO_START);
	else if (errno == NO_END_ERR)
		printf(NO_END);
	else if (errno == NO_LINKS_ERR)
		printf(NO_LINKS);
	else if (errno == INVALID_LINK_ERR)
		printf(INVALID_LINK);
	else if (errno == LARGE_NAME_ERR)
		printf(LARGE_NAME);
	else if (errno == NO_LINK_ROOM_ERR)
		printf(NO_LINK_ROOM);
	else if (errno == DUPLICATE_NAME_ERR)
		printf(DUPLICATE_NAME);
	clean_up(map);
	exit(1);
}
