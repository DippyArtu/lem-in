/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#ifndef _LEM_IN_MAP_STRUCTS_H_
# define _LEM_IN_MAP_STRUCTS_H_

typedef enum 				e_room_type
{
	START = 0,
	NONE = 1,
	END = 2
}							t_room_type;

typedef struct 				s_ant
{
	int 					ant_num;
	char 					*room_name;
}							t_ant;

typedef struct 				s_room_node
{
	char 					*room_name;
	t_room_type 			type;
	int 					x;
	int 					y;
	t_ant					*ant;

	struct 			s_links
	{
		struct s_room_node	*back;
		struct s_room_node	*forward;
		struct s_links		*next;
	}						t_links;
}							room_node;

typedef struct 				s_map
{
	int 					num_steps;
	int 					num_ants;
	room_node 				*start;
	room_node 				*end;
}							t_map;

#endif
