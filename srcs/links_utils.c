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

char 						*get_link_name(char **line, t_map *map)
{
	char 					*name;
	int 					i;

	if (!line || **line == '\0')
		error(INVALID_LINE_ERR, map);
	if (!(name = (char *)malloc(101 * sizeof(char))))
		error(MALLOC_FAIL_ERR, map);
	bzero(name, 101);
	i = 0;

	while (**line != '\0' && **line != '-')
	{
		if (i == 100)
			error(LARGE_NAME_ERR, map);
		name[i++] = **line;
		*line += 1;
	}
	return name;
}

void 						validate_link(char *room1, char *room2, t_map *map)
{
	char 					*val1;
	char 					*val2;
	struct s_link_valid		*validator;
	struct s_link_valid		*next;

	if (!map->links_val)
	{
		map->links_val = init_l_validator();
		map->links_val->link1 = strdup(room1);
		map->links_val->link2 = strdup(room2);
		return;
	}
	validator = map->links_val;
	next = validator->next;
	while (next)
	{
		val1 = validator->link1;
		val2 = validator->link2;
		if (ft_strcmp(room1, val1) == 1)																				//link duplicate (a-b ; a-b)
		{
			if (ft_strcmp(room2, val2) == 1)
				error(DUPLICATE_LINK_ERR, map);
		}
		if (ft_strcmp(room1, val2) == 1)																				//reverse link duplicate (a-b ; b-a)
		{
			if (ft_strcmp(room2, val1))
				error(DUPLICATE_LINK_ERR, map);
		}
		validator = next;
		next = validator->next;
	}
	next = init_l_validator();
	next->link1 = strdup(room1);
	next->link2 = strdup(room2);
	validator->next = next;
}
