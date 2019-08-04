/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:52:15 by fsmith            #+#    #+#             */
/*   Updated: 2019/08/04 21:20:00 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_fill_polygones_from_file(t_engine *eng, t_polygone *polygone,
		t_point_3d *vertex_array, char **str)
{
	int			vert_count;
	int			str_count;

	str_count = 5;
	vert_count = 0;
	polygone->id = ft_atoi(str[1]);
	polygone->type = ft_atoi(str[2]);
	polygone->color = ft_atoi(str[3]);
	polygone->vertices_count = ft_atoi(str[4]);
	polygone->vertices_array = (t_point_3d *)ft_memalloc(sizeof(t_point_3d)
		* polygone->vertices_count);
	while (str_count < 5 + polygone->vertices_count)
		polygone->vertices_array[vert_count++] =
		util_get_vertex_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.vertexes_count, vertex_array, polygone->id);
	eng->stats.polies_count++;
}

void		engine_fill_objects_from_file(t_engine *eng, t_object *object,
		t_polygone *polygone_array, char **str)
{
	int			pol_count;
	int			str_count;

	object->id = ft_atoi(str[1]);
	object->portal = ft_atoi(str[2]);
	object->polies_count = ft_atoi(str[3]);
	object->polies_array = (t_polygone *)ft_memalloc(sizeof(t_polygone)
		* object->polies_count);
	str_count = 4;
	pol_count = 0;
	while (str_count < 4 + object->polies_count)
		object->polies_array[pol_count++] =
		util_get_polygone_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.polies_count, polygone_array, object->id);
	eng->stats.objects_count++;
}

void		engine_fill_sectors_from_file(t_engine *eng, t_sector *sector,
		t_object *objects_array, char **str)
{
	int			obj_count;
	int			str_count;

	sector->id = ft_atoi(str[1]);
	sector->floor = ft_atoi(str[2]);
	sector->ceil = ft_atoi(str[3]);
	sector->objects_count = ft_atoi(str[4]);
	sector->objects_array = (t_object *)ft_memalloc(sizeof(t_object)
		* sector->objects_count);
	str_count = 5;
	obj_count = 0;
	while (str_count < 5 + sector->objects_count)
		sector->objects_array[obj_count++] =
		util_get_object_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.objects_count, objects_array, sector->id);
	eng->stats.sectors_count++;
}
