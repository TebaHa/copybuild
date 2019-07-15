/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 00:38:38 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/15 05:57:05 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int		intersect(t_point_2d a, t_point_2d b, t_point_2d pos)
{
	if (((a.y > pos.y) != (b.y > pos.y)) &&
	(pos.x < (a.x + (b.x - a.x) * (pos.y - a.y) / (b.y - a.y))))
		return (1);
	else
		return (0);
}

int		engine_object_get_sector(t_world *world, t_point_3d pos)
{
	int			res;
	int			s;
	int			i;
	int			k;

	res = -1;
	s = 0;
	while (s < 2)
	{
		i = 0;
		k = 3;
		while (i < world->sectors_array[s].objects_size)
		{
			if (intersect((t_point_2d){world->sectors_array[s].objects_array[i].polies_array[0].vertices[0].x,
			world->sectors_array[s].objects_array[i].polies_array[0].vertices[0].y},
			(t_point_2d){world->sectors_array[s].objects_array[k].polies_array[0].vertices[0].x,
			world->sectors_array[s].objects_array[k].polies_array[0].vertices[0].y}, (t_point_2d){pos.x, pos.y}))
				res = -res;
			k = i;
			i++;
		}
		if (res > 0)
			return (world->sectors_array[s].id);
		s++;
	}
	return (-1);
}
