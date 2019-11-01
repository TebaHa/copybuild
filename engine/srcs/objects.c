/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 00:38:38 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/01 08:32:32 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int		engine_object_get_sector(t_world *world, t_point_3d pos, int start_sect)
{
	t_find_obj	data;

	data.res = -1;
	ft_memset(data.checked_array, 0, MAXSECTORS * sizeof(int));
	engine_clear_checkstack(data.check_stack);
	engine_push_checkstack(data.check_stack, start_sect);
	while ((data.cursect = engine_pop_checkstack(data.check_stack)) >= 0)
	{
		data.i = 0;
		printf("CURSECTOR %d\n", data.cursect);
		while (data.i < world->sectors_array[data.cursect].objects_count)
		{
			engine_check_object(&data, world, pos);
		}
		if (data.res >= 0)
		{
			if (engine_z_coord_check(&world->sectors_array[data.cursect], pos))
				return (data.cursect);
		}
		data.checked_array[data.cursect] = 1;
	}
	return (-1);
}

void	engine_check_object(t_find_obj *d, t_world *world, t_point_3d pos)
{
	if (intersect_sect((t_point_2d){world->sectors_array[d->cursect].
	objects_array[d->i].polies_array[0].vertices_array[0].x,
	world->sectors_array[d->cursect].objects_array[d->i].
	polies_array[0].vertices_array[0].y},
	(t_point_2d){world->sectors_array[d->cursect].objects_array[d->i].
	polies_array[0].vertices_array[1].x,
	world->sectors_array[d->cursect].objects_array[d->i].polies_array[0].
	vertices_array[1].y}, (t_point_2d){pos.x, pos.y}))
		d->res = -d->res;
	if (world->sectors_array[d->cursect].objects_array[d->i].portal >= 0
	&& d->checked_array[world->sectors_array[d->cursect].
	objects_array[d->i].portal] == 0)
		engine_push_checkstack(d->check_stack,
		world->sectors_array[d->cursect].objects_array[d->i].portal);
	d->i++;
}

short	engine_z_coord_check(t_sector *sector, t_point_3d pos)
{
	if (((sector->floor - 5) < pos.z)
	&& ((sector->ceil + 5) > pos.z))
		return (1);
	return (0);
}
