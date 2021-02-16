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

t_matrix 					*init_gl_matrices(void)
{
	t_matrix 				*matrix;

	if (!(matrix = (t_matrix *)malloc(sizeof(t_matrix))))
		error(MALLOC_FAIL_ERR, NULL);

	glm_mat4_identity(matrix->model_mat);
	glm_mat4_identity(matrix->projection_mat);
	glm_mat4_identity(matrix->view_mat);

	matrix->eye[0] = 1.5f;
	matrix->eye[1] = 1.5f;
	matrix->eye[2] = 0.0f;

	matrix->center[0] = 0.0f;
	matrix->center[1] = 0.0f;
	matrix->center[2] = 0.0f;

	matrix->up[0] = 0.0f;
	matrix->up[1] = 0.0f;
	matrix->up[2] = 1.0f;
	return matrix;
}

t_gl						*init_gl_struct(void)
{
	t_gl					*gl;

	if (!(gl = (t_gl *)malloc(sizeof(t_gl))))
		error(MALLOC_FAIL_ERR, NULL);
	gl->window = NULL;
	gl->shaderProgram = 0;
	gl->vertexShader = 0;
	gl->fragmentShader = 0;
	gl->geometryShader = 0;
	gl->vbo = 0;
	gl->vao = 0;
	gl->points = NULL;
	gl->num_points = 0;
	gl->x_max = 0;
	gl->x_min = 0;
	gl->y_max = 0;
	gl->y_min = 0;
	gl->matrix = init_gl_matrices();
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
