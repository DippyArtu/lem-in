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
	int 					num_points;

	num_points = map->num_rooms * 2;
	if (!(map->gl->points = (GLfloat *)malloc(num_points * sizeof(GLfloat))))
		error(MALLOC_FAIL_ERR, map);
	bzero(map->gl->points, num_points);
}

void 						gl_insert_points(t_map *map, t_room_node *room, t_hash_table *table)
{
	GLfloat					*pts;
	static int 				i;

	pts = map->gl->points;
	if (!(ht_search(table, room->room_name)))
	{
		ht_insert(table, room->room_name, room);
		pts[i++] = (GLfloat)room->x;
		pts[i++] = (GLfloat)room->y;
	}
}
