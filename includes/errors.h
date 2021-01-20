/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#ifndef LEM_IN_ERRORS_H
# define LEM_IN_ERRORS_H

# define ARG_NUM_ERR 1
# define OPEN_FILE_ERR 2
# define MALLOC_FAIL_ERR 3
# define FILE_READ_ERR 4
# define ANT_NUM_ERR 5
# define INVALID_LINE_ERR 6
# define INVALID_ROOM_NAME_ERR 7
# define INVALID_COORD_ERR 8
# define START_FLAG_ERR 9
# define END_FLAG_ERR 10
# define NO_START_ERR 11
# define NO_END_ERR 12
# define NO_LINKS_ERR 13
# define INVALID_LINK_ERR 14
# define LARGE_NAME_ERR 15
# define NO_LINK_ROOM_ERR 16

# define USAGE "Usage: ./lem_in *map_file*\n"
# define ARG_NUM "ERROR: Invalid number of arguments\n"
# define MALLOC_FAIL "ERROR: Could not allocate memory\n"

# define OPEN_FILE "ERROR: Could not open the file\n"
# define FILE_READ "ERROR: Error reading a file\n"

# define ANT_NUM "ERROR: Invalid number of ants\n"
# define INVALID_LINE "ERROR: Invalid line in a file\n"
# define INVALID_ROOM_NAME "ERROR: Invalid room name\n"
# define INVALID_COORD "ERROR: Invalid coordinate\n"
# define START_FLAG "ERROR: A map can have only one start room\n"
# define END_FLAG "ERROR: A map can have only one end room\n"
# define NO_START "ERROR: No start room were found\n"
# define NO_END "ERROR: No end room were found\n"
# define NO_LINKS "ERROR: No links between rooms were found\n"

# define INVALID_LINK "ERROR: Invalid link\n"
# define LARGE_NAME "ERROR: Room name is too large — 100 characters max\n"
# define NO_LINK_ROOM "ERROR: Invalid link — room linked doesn't exist\n"

#endif
