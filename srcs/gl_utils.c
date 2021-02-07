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

void 						framebuffer_size_callback(GLFWwindow *window, int width, int height) //---------------------For window resizing
{
	int 				i = 0;
	glViewport(0, 0, width, height);

	if (window) //------------------------------------------------------------------------------------------------------To avoid unused variable comp error
		i++;
}

void 						processInput(GLFWwindow *window) //---------------------------------------------------------Key press capture
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void 						init_gl(t_map *map)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //-------------------------------------------------------------3.2 gl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //-------------------------------------------------------------------------Window is resizable
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);

	map->gl->window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "Lem-in", NULL, NULL); //--------------Creates window
	glfwMakeContextCurrent(map->gl->window);
	glewExperimental = GL_TRUE;
	glewInit();
	if (!map->gl->window)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		exit (1);
	}
	glfwSetFramebufferSizeCallback(map->gl->window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST); //-----------------------------------------------------------------------------------------Enables depth testing
}

void 						terminate_gl(t_gl *gl)
{
	glDeleteVertexArrays(1, &gl->vao);
	glDeleteBuffers(1, &gl->vbo);
	glDeleteProgram(gl->shaderProgram);
	glfwTerminate();
}
