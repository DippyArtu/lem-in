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

void 						error(int errno, t_map *map);

t_map 						*init_map(void);
t_room_node 				*init_room(void);

void 						clean_up(t_map *map);
struct s_room_node 			*free_room(t_room_node *room);

t_map 						*get_map(int fd);

int 						get_rooms(int fd, t_map *map);
int 						process_room(char *line, t_map *map, int flag);
void 						process_comment(char *line, t_map *map, int fd);
void 						get_num_ants(int fd, t_map *map, char *line);

size_t						validate_room_name(char *line, t_map *map);
int 						get_room_coordinate(char **line, t_map *map);
void 						record_room(t_map *map, t_room_node *new_room, int flag);

#endif
