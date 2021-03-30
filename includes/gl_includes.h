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

# define VERTEX_SRC "./shaders/vertex.shader"
# define GEOMETRY_SRC "./shaders/geometry.shader"
# define FRAGMENT_SRC "./shaders/fragment.shader"

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "stb_image.h"
# include <cglm/cglm.h>

//----------------------------------------------------------------------------------------------------------------------Window dimensions
# define SRC_WIDTH 800
# define SRC_HEIGHT 600

typedef struct 				s_matrix
{
	mat4 					model_mat;
	mat4 					projection_mat;
	mat4 					view_mat;

	vec3 					eye;
	vec3 					center;
	vec3 					up;

	GLuint 					model;
}							t_matrix;

typedef struct 				s_gl
{
	GLFWwindow 				*window; //---------------------------------------------------------------------------------GL context window

	GLuint 					vertexShader;
	GLuint 					fragmentShader;
	GLuint 					geometryShader;
	GLuint					shaderProgram;

	GLuint 					vbo;
	GLuint 					vao;

	float 					*points;
	int						num_points;
	int						x_max;
	int						x_min;
	int						y_max;
	int						y_min;
	float					min_room_dist;

	t_matrix 				*matrix;
}							t_gl;

#endif
