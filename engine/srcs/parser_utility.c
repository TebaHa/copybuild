/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:12:50 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/01 14:48:05 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		util_create_world(t_world **world, char **str)
{
	*world = (t_world *)ft_memalloc(sizeof(t_world));
	util_int10_data_filler(&(*world)->id, str[1]);
	util_int10_data_filler(&(*world)->sectors_count, str[2]);
	util_parsing_error_count_handler("sector", "world", str, 2);
	(*world)->renderqueue = (t_item *)ft_memalloc(sizeof(t_item)
		* (*world)->sectors_count);
	(*world)->sectors_array = (t_sector *)ft_memalloc(sizeof(t_sector)
		* (*world)->sectors_count);
}

void		util_create_point_3d(t_engine *eng, t_point_3d *point, char **str)
{
	if (!str[4])
		util_parsing_error_little_data("coordinate", "vertex", str);
	if (str[5])
		util_parsing_error_extra_data("coordinate", "vertex", str);
	util_int10_data_filler(&point->id, str[1]);
	util_float10_data_filler(&point->x, str[2]);
	util_float10_data_filler(&point->y, str[3]);
	util_float10_data_filler(&point->z, str[4]);
	eng->stats.vertexes_count++;
}

void		util_create_polygone(t_engine *eng, t_polygone *polygone,
			t_point_3d *vertex_array, char **str)
{
	int			vert_count;
	int			str_count;

	util_int10_data_filler(&polygone->id, str[1]);
	util_int10_data_filler(&polygone->type, str[2]);
	util_int16_data_filler(&polygone->color, str[3]);
	util_find_texture_by_name(&polygone->texture, eng, str[4]);
	util_int10_data_filler(&polygone->vertices_count, str[5]);
	util_parsing_error_count_handler("vertex", "polygone", str, 5);
	polygone->vertices_array = (t_point_3d *)ft_memalloc(sizeof(t_point_3d)
		* polygone->vertices_count);
	str_count = 6;
	vert_count = 0;
	while (str_count < 6 + polygone->vertices_count)
		polygone->vertices_array[vert_count++] =
		util_get_vertex_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.vertexes_count, vertex_array, polygone->id);
	eng->stats.polies_count++;
}

void		util_create_object(t_engine *eng, t_object *object,
			t_polygone *polygone_array, char **str)
{
	int			pol_count;
	int			str_count;

	util_int10_data_filler(&object->id, str[1]);
	util_int10_data_filler(&object->portal, str[2]);
	util_int10_data_filler(&object->passble, str[3]);
	util_find_texture_by_name(&object->floor_wall_texture, eng, str[4]);
	util_find_texture_by_name(&object->ceil_wall_texture, eng, str[5]);
	util_int10_data_filler(&object->polies_count, str[6]);
	util_parsing_error_count_handler("polygone", "object", str, 6);
	object->polies_array = (t_polygone *)ft_memalloc(sizeof(t_polygone)
		* object->polies_count);
	str_count = 7;
	pol_count = 0;
	while (str_count < 7 + object->polies_count)
		object->polies_array[pol_count++] =
		util_get_polygone_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.polies_count, polygone_array, object->id);
	eng->stats.objects_count++;
}

void		util_create_sector(t_engine *eng, t_sector *sector,
			t_object *objects_array, char **str)
{
	int			obj_count;
	int			str_count;

	util_int10_data_filler(&sector->id, str[1]);
	util_int10_data_filler(&sector->floor, str[2]);
	util_int10_data_filler(&sector->ceil, str[3]);
	util_find_texture_by_name(&sector->floor_texture, eng, str[4]);
	util_find_texture_by_name(&sector->ceil_texture, eng, str[5]);
	util_int10_data_filler(&sector->objects_count, str[6]);
	util_parsing_error_count_handler("object", "sector", str, 6);
	sector->objects_array = (t_object *)ft_memalloc(sizeof(t_object)
		* sector->objects_count);
	str_count = 7;
	obj_count = 0;
	while (str_count < 7 + sector->objects_count)
		sector->objects_array[obj_count++] =
		util_get_object_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.objects_count, objects_array, sector->id);
	eng->stats.sectors_count++;
}

void		util_find_texture_by_name(t_image **dst, t_engine *eng,
			char *name)
{
	int		i;
	int		find;

	i = 0;
	find = 0;
	while (i < eng->stats.textures_count)
	{
		if (!ft_strcmp(name, eng->texture_buffer[i]->filename))
		{
			*dst = &eng->texture_buffer[i]->texture;
			find = 1;
		}
		i++;
	}
	if (i >= eng->stats.textures_count && !find)
		util_parsing_error_no_texture(dst, eng, name);
}
