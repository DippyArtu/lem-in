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

void 						createVBO(t_gl *gl, GLfloat *points)
{
	glGenBuffers(1, &gl->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*points), &points, GL_STATIC_DRAW);
}

void						createVAO(t_gl *gl)
{
	glGenVertexArrays(1, &gl->vao);
	glBindVertexArray(gl->vao);
}
