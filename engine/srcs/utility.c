/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:14:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/09 21:34:06 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_push_renderstack(t_item *renderqueue, t_item item)
{
	int	i;

	i = 0;
	while (renderqueue[i].sectorno >= 0)
		i++;
	while ((i + 1) < MAXSECTORS && i >= 0)
	{
		renderqueue[i + 1] = renderqueue[i];
		i--;
	}
	renderqueue[0] = item;
}

t_item		engine_pop_renderstack(t_item *renderqueue)
{
	t_item	res;
	int	i;

	i = 0;
	res = renderqueue[0];
	while ((i + 1) < MAXSECTORS && renderqueue[i].sectorno >= 0)
	{
		renderqueue[i] = renderqueue[i + 1];
		i++;
	}
	return (res);
}

void	engine_clear_renderstack(t_item *renderqueue)
{
	int	i;

	i = 0;
	while (i < MAXSECTORS)
	{
		renderqueue[i].sectorno = -1;
		i++;
	}
}

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

t_point_3d		util_get_vertex_from_buff_by_id(int id, int size, t_point_3d *vertexes)
{
	t_point_3d	res;
	int			i;

	i = 0;
	while (i < size)
	{
		if (vertexes[i].id == id)
		break;
		i++;
	}
	return (vertexes[i]);
}

t_polygone		util_get_polygone_from_buff_by_id(int id, int size, t_polygone *polies, int object_id)
{
	t_polygone	res;
	int			i;

	i = 0;
	while (i < size)
	{
		if (polies[i].id == id)
		break;
		i++;
	}
	return (polies[i]);
}

t_object		util_get_object_from_buff_by_id(int id, int size, t_object *objects, int sector_id)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (objects[i].id == id)
		break;
		i++;
	}
	return (objects[i]);
}

t_sprobject		util_get_sprobject_from_buff_by_id(int id, int size, t_sprobject *sprobjects, int sector_id)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (sprobjects[i].id == id)
			break;
		i++;
	}
	return (sprobjects[i]);
}

t_sprite		util_get_sprite_from_buff_by_id(int id, int size, t_sprite *sprites)
{
	t_sprite	res;
	int			i;

	if (id < 0)
	{
		/* Дописать кусок обработки, когда просто нет отображения никакого */
		ft_putendl("Вернуть пустой спрайт");
		exit(PARSING_ERROR);
	}
	i = 0;
	while (i < size)
	{
		if (sprites[i].id == id)
			break;
		i++;
	}
	return (sprites[i]);
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

void			util_release_read_buffers(t_point_3d *vertex_buff, t_polygone *polies_buff,
								t_object *object_buff)
{
	free(vertex_buff);
	free(polies_buff);
	free(object_buff);
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
