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

//---------------------------------------------------------------------------------------------------------------------- errors.c
void 						error(int errno, t_map *map);

//---------------------------------------------------------------------------------------------------------------------- init.c
t_map 						*init_map(void);
t_room_node 				*init_room(void);
struct s_links				*init_link(void);

//---------------------------------------------------------------------------------------------------------------------- clean_up.c
void 						clean_up(t_map *map);
struct s_room_node 			*free_room(t_room_node *room);
void 						free_links(t_room_node *room);

//---------------------------------------------------------------------------------------------------------------------- parse_map.c
t_map 						*get_map(int fd);

//---------------------------------------------------------------------------------------------------------------------- parse_rooms.c
char 						*get_rooms(int fd, t_map *map);
int 						process_room(char *line, t_map *map, int flag);
void 						process_comment(char *line, t_map *map, int fd);
void 						get_num_ants(int fd, t_map *map, char *line);

//---------------------------------------------------------------------------------------------------------------------- room_utils.c
size_t						validate_room_name(char *line, t_map *map);
int 						get_room_coordinate(char **line, t_map *map);
void 						record_room(t_map *map, t_room_node *new_room, int flag);

//---------------------------------------------------------------------------------------------------------------------- parse_links.c
void 						get_links(char *line, int fd, t_map *map);
void 						process_link(char *line, t_map *map);
void 						create_link(t_map *map, char *name1, char *name2);
void 						insert_link(struct s_room_node *room_curr, struct s_room_node *room_insert, int flag);

//---------------------------------------------------------------------------------------------------------------------- link_utils.c
char 						*get_link_name(char **line, t_map *map);
struct s_room_node			*find_room(t_map *map, char *name);

#endif
