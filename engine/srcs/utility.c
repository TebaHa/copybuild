/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:14:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/11 13:13:34 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		util_release_char_matrix(char **mtrx)
{
	int		i;

	i = 0;
	while (mtrx[i] != NULL)
	{
		free(mtrx[i]);
		i++;
	}
	free(mtrx);
}

void			util_release_vertex_buffer(t_point_3d *vertex_buff)
{
	free(vertex_buff);
}

void			util_release_polies_buffer(t_polygone *polies_buff, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		util_release_vertex_buffer(polies_buff[i].vertices_array);
		i++;
	}
	free(polies_buff);
}

void			util_release_objects_buffer(t_object *object_buff, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		util_release_polies_buffer(object_buff[i].polies_array, object_buff[i].polies_count);
		i++;
	}
	free(object_buff);
}

void			util_release_sectors_buffer(t_sector *sector_buff, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		util_release_objects_buffer(sector_buff[i].objects_array, sector_buff[i].objects_count);
		i++;
	}
	free(sector_buff);
}

void			util_release_world(t_world *world)
{
	util_release_sectors_buffer(world->sectors_array, world->sectors_count);
	free(world->renderqueue);
	free(world);
}

void			point_swap_3(t_fix_point_3d *t0, t_fix_point_3d *t1)
{
	t_fix_point_3d		tmp;

	tmp.x = t0->x;
	tmp.y = t0->y;
	tmp.z = t0->z;
	t0->x = t1->x;
	t0->y = t1->y;
	t0->z = t1->z;
	t1->x = tmp.x;
	t1->y = tmp.y;
	t1->z = tmp.z;
}

void			point_swap_2(t_fix_point_2d *t0, t_fix_point_2d *t1)
{
	t_fix_point_2d		tmp;

	tmp.x = t0->x;
	tmp.y = t0->y;
	t0->x = t1->x;
	t0->y = t1->y;
	t1->x = tmp.x;
	t1->y = tmp.y;
}
