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

void 						gl_init_points(t_map *map)
{
	map->gl->num_points = map->num_rooms * 2;
	if (!(map->gl->points = (float *)malloc(map->gl->num_points * sizeof(float))))
		error(MALLOC_FAIL_ERR, map);
	bzero(map->gl->points, map->gl->num_points);
}

/*
 * Scale function:
 *
 *        M - R_min
 * M =  --------------- * (T_max - T_min) + T_min
 *       R_max - R_min
 *
 * R_min — minimum of the range of input
 * R_max — maximum of the range of input
 * T_min — minimum of the target range
 * T_max — maximum of the target range
 * M — input value
 *
 * If coordinates are on a straight line, delta would equal to 0
 * to avoid the division by zero, in that case, delta is set to 1
 */
void						gl_scale_points(t_gl *gl) //----------------------------------------------------------------Target range: -0.75; 0.75
{
	int 					i;
	float					delta_x;
	float					delta_y;
	float 					x;
	float 					y;
	float 					prev_x;
	float 					prev_y;

	i = 0;
	prev_x = 0;
	prev_y = 0;
	if (!(delta_x = (float)(gl->x_max - gl->x_min)))
		delta_x = 1.0f;
	if (!(delta_y = (float)(gl->y_max - gl->y_min)))
		delta_y = 1.0f;
	while (i < gl->num_points)
	{
		gl->points[i] = ((gl->points[i] - (float)gl->x_min) / delta_x) * 1.5f - 0.75f;
		x = gl->points[i];
		i++;
		gl->points[i] = ((gl->points[i] - (float)gl->y_min) / delta_y) * 1.5f - 0.75f;
		y = gl->points[i];
		i++;
		gl_calc_room_dist(gl, x, y, prev_x, prev_y);
		prev_x = x;
		prev_y = y;
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

void						gl_set_attrib_ptr(t_gl *gl, char *attrib_name, GLint num_vals, int stride, int offset)
{
	GLuint 					attrib;

	attrib = glGetAttribLocation(gl->shaderProgram, attrib_name);
	glVertexAttribPointer(attrib, num_vals, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(offset * sizeof(float)));
	glEnableVertexAttribArray(attrib);
}
