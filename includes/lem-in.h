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
void 				process_line(t_map *map);

void 				error(int errno, t_map *map);
void 				clean_up(t_map *map);

#endif
