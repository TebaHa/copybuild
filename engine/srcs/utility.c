/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:14:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/04 16:46:14 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_push_renderstack(int *renderqueue, int sector_id)
{
	int	i;

	i = 0;
	while (renderqueue[i] >= 0)
		i++;
	while ((i + 1) < MAXSECTORS && i >= 0)
	{
		renderqueue[i + 1] = renderqueue[i];
		i--;
	}
	renderqueue[0] = sector_id;
}

int		engine_pop_renderstack(int *renderqueue)
{
	int	res;
	int	i;

	i = 0;
	res = renderqueue[0];
	while ((i + 1) < MAXSECTORS && renderqueue[i] >= 0)
	{
		renderqueue[i] = renderqueue[i + 1];
		i++;
	}
	return (res);
}

void	engine_clear_renderstack(int *renderqueue)
{
	int	i;

	i = 0;
	while (i < MAXSECTORS)
	{
		renderqueue[i] = -1;
		i++;
	}
}

t_point_3d	*util_create_point_3d(float x, float y, float z)
{
	t_point_3d	*point;

	point = (t_point_3d *)ft_memalloc(sizeof(t_point_3d));
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}

t_world		*util_create_world(int id, int sector_count)
{
	t_world	*world;

	world = (t_world *)ft_memalloc(sizeof(t_world));
	world->id = id;
	world->sectors_count = sector_count;
	world->renderqueue = (int *)ft_memalloc(sizeof(int) * sector_count);
	world->sectors_array = (t_sector *)ft_memalloc(sizeof(t_sector) *
			sector_count);
	return (world);
}

t_sector	*util_create_sector(int id, int floor, int ceil, int object_count)
{
	t_sector	*sector;

	sector = (t_sector *)ft_memalloc(sizeof(t_sector));
	sector->ceil = ceil;
	sector->floor = floor;
	sector->id = id;
	sector->objects_count = object_count;
	sector->objects_array = (t_object *)ft_memalloc(sizeof(t_object) * object_count);
	return (sector);
}

t_object	*util_create_object(int id, int portal, int polies_count)
{
	t_object	*object;

	object = (t_object *)ft_memalloc(sizeof(t_object));
	object->id = id;
	object->portal = portal;
	object->polies_count = polies_count;
	object->polies_array = (t_polygone *)ft_memalloc(sizeof(t_polygone) * polies_count);
	return (object);
}

t_polygone	*util_create_polygone(int id, int type, int vertex_count)
{
	t_polygone	*polygone;

	polygone = (t_polygone *)ft_memalloc(sizeof(t_polygone));
	polygone->id = id;
	polygone->type = type;
	polygone->vertices_count = vertex_count;
	polygone->vertices_array = (t_point_3d *)ft_memalloc(sizeof(t_point_3d) * vertex_count);
	return (polygone);
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

t_point_3d		util_get_vertex_from_buff_by_id(int id, int size,
		t_point_3d *vertexes)
{
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

t_polygone		util_get_polygone_from_buff_by_id(int id, int size,
		t_polygone *polies)
{
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

t_object		util_get_object_from_buff_by_id(int id, int size, t_object *objects)
{
	t_object	res;
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

void	point_swap(t_point_3d *t0, t_point_3d *t1)
{
	t_point_3d		tmp;

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
