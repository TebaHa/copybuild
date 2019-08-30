/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 00:38:38 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/30 21:15:33 by zytrams          ###   ########.fr       */
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

int		engine_object_get_sector(t_world *world, t_point_3d pos, int start_sect)
{
	int			check_stack[MAXSECTORS];
	int			checked_array[MAXSECTORS];
	int			res;
	int			cursect;
	int			i;
	int			j;
	int			k;

	res = -1;
	ft_memset(checked_array, 0, MAXSECTORS * sizeof(int));
	engine_clear_checkstack(check_stack);
	engine_push_checkstack(check_stack, start_sect);
	while ((cursect = engine_pop_checkstack(check_stack)) >= 0)
	{
		i = 0;
		while (i < world->sectors_array[cursect].objects_count)
		{
			if (intersect((t_point_2d){world->sectors_array[cursect].objects_array[i].polies_array[0].vertices_array[0].x,
			world->sectors_array[cursect].objects_array[i].polies_array[0].vertices_array[0].y},
			(t_point_2d){world->sectors_array[cursect].objects_array[i].polies_array[0].vertices_array[1].x,
			world->sectors_array[cursect].objects_array[i].polies_array[0].vertices_array[1].y}, (t_point_2d){pos.x, pos.y}))
				res = -res;
			if (world->sectors_array[cursect].objects_array[i].portal >= 0 && checked_array[world->sectors_array[cursect].objects_array[i].portal] == 0)
				engine_push_checkstack(check_stack, world->sectors_array[cursect].objects_array[i].portal);
			i++;
		}
		if (res >= 0)
			return (cursect);
		checked_array[cursect] = 1;
	}
	return (-1);
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
