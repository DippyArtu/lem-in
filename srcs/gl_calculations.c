/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#include "lem-in.h"

void						gl_calc_room_size(t_map *map)
{
	GLuint 					uni_length;
	float 					length;

	if (map)
		printf("gl\n");

	length = 0.05f;
	uni_length = glGetUniformLocation(map->gl->shaderProgram, "len");
	glUniform1f(uni_length, length);
}

void 						gl_calc_transforms(t_map *map)
{
	t_matrix 				*matrix;
	GLuint		 			view;
	GLuint		 			projection;

	matrix = map->gl->matrix;
	matrix->model = glGetUniformLocation(map->gl->shaderProgram, "model");
	glUniformMatrix4fv(matrix->model, 1, GL_FALSE, (float *)matrix->model_mat);

	glm_lookat(matrix->eye, matrix->center, matrix->up, matrix->view_mat);
	view = glGetUniformLocation(map->gl->shaderProgram, "view");
	glUniformMatrix4fv(view, 1, GL_FALSE, (float *)matrix->view_mat);

	glm_perspective(glm_rad(45.0f), (SRC_WIDTH / SRC_HEIGHT), 1.0f, 10.0f, matrix->projection_mat);
	projection = glGetUniformLocation(map->gl->shaderProgram, "proj");
	glUniformMatrix4fv(projection, 1, GL_FALSE, (float *)matrix->projection_mat);
}
