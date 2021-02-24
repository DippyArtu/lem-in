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

void						points_test(t_map *map);

//TODO now draw corridors between the points
void 						run_graphics(t_map *map)
{
	t_gl 					*gl;

	gl = map->gl;
	gl_scale_points(gl);

	points_test(map);

	init_gl(map);
	createVAO(gl);
	createVBO(gl, gl->num_points * sizeof(float), (GLfloat *)gl->points);
	makeShaderProgram(gl);
	gl_set_attrib_ptr(gl, "pos", 2,0, 0);

	gl_calc_room_size(map);
	gl_calc_transforms(map);

	gl_render(map);

	terminate_gl(gl);
}

void						gl_render(t_map *map)
{
	float					time;

	while (!glfwWindowShouldClose(map->gl->window))
	{
		processInput(map->gl->window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Calculate transformation
		time = glfwGetTime();
		glm_mat4_identity(map->gl->matrix->model_mat);
		glm_rotate(map->gl->matrix->model_mat, (0.25f * time * glm_rad(180.0f)), map->gl->matrix->up);
		glUniformMatrix4fv(map->gl->matrix->model, 1, GL_FALSE, (float *)map->gl->matrix->model_mat);

		//Render frames
		glDrawArrays(GL_POINTS, 0, map->num_rooms);

		glfwSwapBuffers(map->gl->window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
