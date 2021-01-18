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

# define USAGE "Usage: ./lem_in *map_file*\n"
# define ARG_NUM "Invalid number of arguments\n"
# define MALLOC_FAIL "Could not allocate memory\n"

# define OPEN_FILE "Could not open the file\n"
# define FILE_READ "Error reading a file\n"

# define ANT_NUM "Invalid number of ants\n"
# define INVALID_LINE "Invalid line in a file\n"
# define INVALID_ROOM_NAME "Invalid room name\n"
# define INVALID_COORD "Invalid coordinate\n"
# define START_FLAG "A map can have only one start room\n"
# define END_FLAG "A map can have only one end room\n"

#endif
