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

# include "gl_includes.h"

/*
 * Defines whether the room is a start, end or neither in a map
 */
typedef enum 				e_room_type
{
	START = 0,
	NONE = 1,
	END = 2
}							t_room_type;

/*
 * Keeps track of ant data:
 *
 * - *ant_num* is an ant ID (from 0 to MAXINT)
 * - *room_name* is a name of the room in which an ant is located currently
 */
typedef struct 				s_ant
{
	int 					ant_num;
	char 					*room_name;
}							t_ant;

/*
 * Used to keep track of the map room structure:
 *
 * - *room_name* is a name of the room (duh)
 * - *type* is a room specifier (start/end/neither)
 * - *x* and *y* are the coordinates of the room
 * - *ant* keeps track of an ant located in this room
 * - *room_next* is used to store the rooms as a linked list, before the
 * link structure between the rooms is processed
 *
 * Struct *s_links* defines the links structure of this room to other rooms:
 *
 * - *back* is the room which leads to this room
 * - *forward* is the room to which this room leads
 * - *next* is another instance of *s_links* structure to describe other connections
 * (in case the room leads to more then one room)
 */
typedef struct 				s_room_node
{
	char 					*room_name;
	t_room_type 			type;
	int 					x;
	int 					y;
	t_ant					*ant;

	struct 					s_links
	{
		struct s_room_node	*back;
		struct s_room_node	*forward;
		struct s_links		*next;
	}						*links;
}							t_room_node;

# ifndef _HASH_STRUCT_
 # define _HASH_STRUCT_
/*
 * Stores key-value pairs
 */
typedef struct 				s_hash_item
{
	char 					*key;
	t_room_node 			*value;
}							t_hash_item;

/*
 * Hash table stores an array of pointers to items as well as its size and how full it is
 */
typedef	struct 				s_hash_table
{
	int 					size;
	int 					base_size;
	int 					count;
	t_hash_item 			**items;
}							t_hash_table;
# endif

/*
 * Used for link validation
 * *links* stores 2 links being processed
 * *next* points to new instance of structure
 */
typedef struct 				s_link_valid
{
	char 					*link1;
	char 					*link2;
	struct s_link_valid		*next;
}							t_link_valid;

/*
 * Defines a map:
 *
 * - *num_steps* keeps track of how many steps taken in the solution of the map
 * - *num_ants* defines how many ants there are in a map
 * - *start* points to the beginning of the map
 * - *end* points to the end of the map
 * - *dummy* is a dummy room struct used as a flag for existing coordinates
 * - *coordinates* is used to make sure no duplicate coordinates are passed
 * - *rooms_hash* is used to store the rooms read from the map file
 * - *links_val* points to list for link validation
 */
typedef struct 				s_map
{
	int 					num_steps;
	int 					num_ants;
	int						num_rooms;
	t_room_node 			*start;
	t_room_node 			*end;

	t_room_node 			*dummy;
	t_hash_table 			*coordinates;
	t_hash_table 			*rooms_hash;

	struct s_link_valid		*links_val;

	t_gl					*gl;
}							t_map;

#endif
