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

struct s_links				*init_link(void)
{
	struct s_links			*link;

	if (!(link = (struct s_links *)malloc(sizeof(struct s_links))))
		error(MALLOC_FAIL_ERR, NULL);
	link->next = NULL;
	link->back = NULL;
	link->forward = NULL;
	return link;
}

t_room_node 				*init_room(void)
{
	t_room_node 			*room;

	if (!(room = (t_room_node *)malloc(sizeof(t_room_node))))
		error(MALLOC_FAIL_ERR, NULL);
	room->room_name = NULL;
	room->type = NONE;
	room->x = 0;
	room->y = 0;
	room->ant = NULL;
	room->links = NULL;
	return room;
}

struct s_link_valid			*init_l_validator(void)
{
	struct s_link_valid		*validator;

	if (!(validator = (struct s_link_valid *)malloc(sizeof(struct s_link_valid))))
		error(MALLOC_FAIL_ERR, NULL);

	validator->link1 = NULL;
	validator->link2 = NULL;
	validator->next = NULL;
	return validator;
}

t_gl						*init_gl_struct(void)
{
	t_gl					*gl;

	if (!(gl = (t_gl *)malloc(sizeof(t_gl))))
		error(MALLOC_FAIL_ERR, NULL);
	gl->window = NULL;
	return gl;
}

t_map 						*init_map(int mode)
{
	t_map 					*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		error(MALLOC_FAIL_ERR, NULL);
	map->num_steps = 0;
	map->num_ants = 0;
	map->num_rooms = 0;
	map->start = NULL;
	map->end = NULL;
	map->rooms_hash = ht_new();

	map->coordinates = ht_new();
	map->dummy = init_room();
	map->dummy->room_name = strdup("dummy room");
	map->links_val = NULL;
	map->gl = NULL;

	if (mode == GRAPHICS_ON)
		map->gl = init_gl_struct();
	return map;
}
