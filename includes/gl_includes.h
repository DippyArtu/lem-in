/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#ifndef LEM_IN_GL_INCLUDES_H
# define LEM_IN_GL_INCLUDES_H

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "stb_image.h"
# include <cglm/cglm.h>

//----------------------------------------------------------------------------------------------------------------------Window dimensions
# define SRC_WIDTH 800
# define SRC_HEIGHT 600

typedef struct 				s_gl
{
	GLFWwindow 				*window; //---------------------------------------------------------------------------------GL context window

	GLuint 					vertexShader;
	GLuint 					fragmentShader;
	GLuint 					geometryShader;
	GLuint					shaderProgram;

	GLuint 					vbo;
	GLuint 					vao;
}							t_gl;

#endif
