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

//TODO normalize points
//TODO clean up the render function
//TODO figure out how to scale room-cube sized depending on number of rooms and distance between them
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

	gl_render(map);

	terminate_gl(gl);
}

void						gl_render(t_map *map)
{
	//Set up transformation matrices
	mat4 				model_mat = GLM_MAT4_IDENTITY_INIT;
	mat4				projection_mat = GLM_MAT4_IDENTITY_INIT;
	mat4				view_mat = GLM_MAT4_IDENTITY_INIT;

	GLuint 				model;
	model = glGetUniformLocation(map->gl->shaderProgram, "model");
	glUniformMatrix4fv(model, 1, GL_FALSE, (float *)model_mat);

	GLuint		 		view;
	vec3 				eye = {1.5f, 1.5f, 0.0f};
	vec3 				center = {0.0f, 0.0f, 0.0f};
	vec3 				up = {0.0f, 0.0f, 1.0f};
	glm_lookat(eye, center, up, view_mat);
	view = glGetUniformLocation(map->gl->shaderProgram, "view");
	glUniformMatrix4fv(view, 1, GL_FALSE, (float *)view_mat);

	GLuint		 		projection;
	glm_perspective(glm_rad(45.0f), (SRC_WIDTH / SRC_HEIGHT), 1.0f, 10.0f, projection_mat);
	projection = glGetUniformLocation(map->gl->shaderProgram, "proj");
	glUniformMatrix4fv(projection, 1, GL_FALSE, (float *)projection_mat);



	float				time;
	while (!glfwWindowShouldClose(map->gl->window))
	{
		processInput(map->gl->window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Calculate transformation
		time = glfwGetTime();
		glm_mat4_identity(model_mat);
		glm_rotate(model_mat, (0.25f * time * glm_rad(180.0f)), up);
		glUniformMatrix4fv(model, 1, GL_FALSE, (float *)model_mat);

		//Render frames
		glDrawArrays(GL_POINTS, 0, map->num_rooms);

		glfwSwapBuffers(map->gl->window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
