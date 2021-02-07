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

//TODO rly idk what but yeah deal with it
void 						run_visuals(t_map *map)
{
	init_gl(map);
	makeShaderProgram(map->gl);

	GLfloat 			points[] = {
		//  Coordinates             Color
		-0.45f,  0.45f, -0.45f, 1.0f, 0.0f, 0.0f,
		0.45f,  0.45f, -0.45f, 0.0f, 1.0f, 0.0f,
		0.45f, -0.45f, -0.45f, 0.0f, 0.0f, 1.0f,
		-0.45f, -0.45f, -0.45f, 1.0f, 1.0f, 0.0f,
		-0.45f,  0.45f,  0.45f, 0.0f, 1.0f, 1.0f,
		0.45f,  0.45f,  0.45f, 1.0f, 0.0f, 1.0f,
		0.45f, -0.45f,  0.45f, 1.0f, 0.5f, 0.5f,
		-0.45f, -0.45f,  0.45f, 0.5f, 1.0f, 0.5f
	};
	createVBO(map->gl, points);
	createVAO(map->gl);


	//--------------------------------------------------------------------------------------------------------------------
	// Specify layout of point data
	GLint 				posAttrib = glGetAttribLocation(map->gl->shaderProgram, "pos");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLint				colAttrib = glGetAttribLocation(map->gl->shaderProgram, "color");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(colAttrib);

	//Set up transformation matrices
	mat4 				model_mat = GLM_MAT4_IDENTITY_INIT;
	mat4				projection_mat = GLM_MAT4_IDENTITY_INIT;
	mat4				view_mat = GLM_MAT4_IDENTITY_INIT;

	GLuint 				model;
	model = glGetUniformLocation(map->gl->shaderProgram, "model");
	glUniformMatrix4fv(model, 1, GL_FALSE, (float *)model_mat);

	GLuint		 		view;
	vec3 				eye = {1.5f, 1.5f, 2.0f};
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
		glDrawArrays(GL_POINTS, 0, 8);

		glfwSwapBuffers(map->gl->window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	//--------------------------------------------------------------------------------------------------------------------


	terminate_gl(map->gl);
}
