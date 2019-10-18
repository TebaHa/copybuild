/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 00:38:38 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 18:16:57 by zytrams          ###   ########.fr       */
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
		while (data.i < world->sectors_array[data.cursect].objects_count)
		{
			engine_check_object(&data, world, pos);
		}
		if (data.res >= 0)
			return (data.cursect);
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
	&& world->sectors_array[d->cursect].objects_array[d->i].portal != 4
	&& d->checked_array[world->sectors_array[d->cursect].
	objects_array[d->i].portal] == 0)
		engine_push_checkstack(d->check_stack,
		world->sectors_array[d->cursect].objects_array[d->i].portal);
	d->i++;
}

void	engine_push_checkstack(int *stack, int sect)
{
	int	i;

	i = 0;
	while (stack[i] >= 0)
		i++;
	while ((i + 1) < MAXSECTORS && i >= 0)
	{
		stack[i + 1] = stack[i];
		i--;
	}
	stack[0] = sect;
}

int		engine_pop_checkstack(int *stack)
{
	int	res;
	int	i;

	i = 0;
	res = stack[0];
	while ((i + 1) < MAXSECTORS && stack[i] >= 0)
	{
		stack[i] = stack[i + 1];
		i++;
	}
	return (res);
}

void	engine_clear_checkstack(int *stack)
{
	int	i;

	i = 0;
	while (i < MAXSECTORS)
	{
		stack[i] = -1;
		i++;
	}
}
