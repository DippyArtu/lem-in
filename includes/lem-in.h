/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#ifndef _LEM_IN_H_
# define _LEM_IN_H_

# include "stdio.h"
# include "ctype.h"

# include <libft.h>
# include <map_structs.h>
# include <errors.h>

t_map 				*init_map(void);

t_map 				*get_map(int fd);
void 				read_map(int fd, t_map *map);
void 				process_room(char *line, t_map *map, int flag);
void 				process_comment(char *line, t_map *map, int fd);
void 				get_num_ants(int fd, t_map *map, char *line);

void 				error(int errno, t_map *map);
void 				clean_up(t_map *map);

#endif
