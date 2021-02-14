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

GLuint 						createShader(GLenum type, char **src) //----------------------------------------------------Shader compiler helper function
{
	char 				buffer[512];
	GLint 				status;
	GLuint 				shader;

	bzero(buffer, 512);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar * const *)src, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status); //---------------------------------------------------------------Checking the compilation status
	if (status != GL_TRUE)
	{
		glGetShaderInfoLog(shader, 512, NULL, buffer); //---------------------------------------------------------------Writes compilation log (first 512 chars) into buffer string
		if (type == GL_VERTEX_SHADER)
			printf("Vertex ");
		else if (type == GL_FRAGMENT_SHADER)
			printf("Fragment ");
		else if (type == GL_GEOMETRY_SHADER)
			printf("Geometry ");
		printf("shader comp failed:\n");
		printf("%s\n", buffer); //--------------------------------------------------------------------------------------Displays log
		exit(1);
	}
	return shader;
}

char						*readShaderSource(char *src_name)
{
	int						i;
	int						fd;
	char 					*src_string;

	if (!(src_string = (char *)malloc(10000 * sizeof(char))))
		error(MALLOC_FAIL_ERR, NULL);
	bzero(src_string, 10000);
	i = 0;
	fd = open(src_name, O_RDONLY);
	if (fd == 0 || fd == -1)
		error(OPEN_FILE_ERR, NULL);
	while (read(fd, &src_string[i], 1))
		i++;
	close(fd);
	return src_string;
}

void 						createProgram(t_gl *gl)
{
	char 				buffer[512];
	GLint 				status;

	bzero(buffer, 512);
	gl->shaderProgram = glCreateProgram();
	if (gl->vertexShader)
		glAttachShader(gl->shaderProgram, gl->vertexShader);
	if (gl->fragmentShader)
		glAttachShader(gl->shaderProgram, gl->fragmentShader);
	if (gl->geometryShader)
		glAttachShader(gl->shaderProgram, gl->geometryShader);
	glLinkProgram(gl->shaderProgram);
	glGetProgramiv(gl->shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetProgramInfoLog(gl->shaderProgram, 512, NULL, buffer);
		printf("Shader program link failed::\n");
		printf("%s\n", buffer); //--------------------------------------------------------------------------------------Displays log on failure
		exit(1);
	}
	if (gl->vertexShader)
		glDeleteShader(gl->vertexShader);
	if (gl->fragmentShader)
		glDeleteShader(gl->geometryShader);
	if (gl->geometryShader)
		glDeleteShader(gl->geometryShader);
	glUseProgram(gl->shaderProgram);
}

void 						makeShaderProgram(t_gl *gl)
{
	char 					*vertex_source;
	char 					*fragment_source;
	char					*geometry_source;
	char 					**vertex_s;
	char 					**fragment_s;
	char 					**geometry_s;

	vertex_s = NULL;
	fragment_s = NULL;
	geometry_s = NULL;

	vertex_source = readShaderSource("./shaders/vertex.shader");
	vertex_s = &vertex_source;
	fragment_source = readShaderSource("./shaders/fragment.shader");
	fragment_s = &fragment_source;
	geometry_source = readShaderSource("./shaders/geometry_cubes.shader");
	geometry_s = &geometry_source;

	gl->vertexShader = createShader(GL_VERTEX_SHADER, vertex_s);
	gl->fragmentShader = createShader(GL_FRAGMENT_SHADER, fragment_s);
	gl->geometryShader = createShader(GL_GEOMETRY_SHADER, geometry_s);

	createProgram(gl);
	vertex_s = NULL;
	fragment_s = NULL;
	geometry_s = NULL;
	free(vertex_source);
	free(fragment_source);
	free(geometry_source);
}
