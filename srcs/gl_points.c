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

//TODO normalize points between -1; 1 to float, make sure no division by zero occurs
//TODO now it normalizes to 0; 1
void 						gl_init_points(t_map *map)
{
	map->gl->num_points = map->num_rooms * 2;
	if (!(map->gl->points = (float *)malloc(map->gl->num_points * sizeof(float))))
		error(MALLOC_FAIL_ERR, map);
	bzero(map->gl->points, map->gl->num_points);
}

void						gl_normalize_points(t_gl *gl)
{
	int 					i;
	float					delta_x;
	float					delta_y;

	i = 0;
	delta_x = (float)(gl->x_max - gl->x_min);
	delta_y = (float)(gl->y_max - gl->y_min);
	while (i < gl->num_points)
	{
		gl->points[i] = (gl->points[i] - (float)gl->x_min) / delta_x;
		i++;
		gl->points[i] = (gl->points[i] - (float)gl->y_min) / delta_y;
		i++;
	}
}

void 						gl_insert_points(t_map *map, t_room_node *room, t_hash_table *table)
{
	float					*pts;
	static int 				i;

	pts = map->gl->points;
	if (!(ht_search(table, room->room_name)))
	{
		ht_insert(table, room->room_name, room);
		pts[i++] = (float)room->x;
		pts[i++] = (float)room->y;

		if (room->x > map->gl->x_max)
			map->gl->x_max = room->x;
		if (room->x < map->gl->x_min)
			map->gl->x_min = room->x;
		if (room->y > map->gl->y_max)
			map->gl->y_max = room->y;
		if (room->y < map->gl->y_min)
			map->gl->y_min = room->y;
	}
}

void						gl_set_attrib_ptr(t_gl *gl, char *attrib_name, GLint num_vals, GLboolean normalize, int stride, int offset)
{
	GLuint 					attrib;

	attrib = glGetAttribLocation(gl->shaderProgram, attrib_name);
	glVertexAttribPointer(attrib, num_vals, GL_FLOAT, normalize, stride * sizeof(float), (void *)(offset * sizeof(float)));
	glEnableVertexAttribArray(attrib);
}
