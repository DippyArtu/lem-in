/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#include <lem-in.h>

int							main(int argc, char **argv)
{
	t_map 					*map;
	int 					fd;

	//---------------------------------------------- hash
	test_hash();
	exit(0);
	//---------------------------------------------- hash exit(0)

	fd = 0;
	map = NULL;

	if (argc != 2)
		error(ARG_NUM_ERR, NULL);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error(OPEN_FILE_ERR, NULL);

	//get map
	map = get_map(fd);
	close(fd);

	//---------------------------------------------- test stuff
	printf("num ants: %i\n\n", map->num_ants);

	struct s_room_node		*tmp;
	tmp = map->rooms_head;
	while (1)
	{
		printf("name: %s		", tmp->room_name);
		printf("x: %i		", tmp->x);
		printf("y: %i		", tmp->y);
		printf("type: %i\n", tmp->type);
		if (!tmp->room_next)
			break;
		tmp = tmp->room_next;
	}
	printf("\nStart room name: %s\n", map->start->room_name);
	printf("\nEnd room name: %s\n", map->end->room_name);
	//----------------------------------------------

	clean_up(map);

	return 0;
}
