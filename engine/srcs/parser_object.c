/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_object	*engine_read_objects_from_file(t_engine *eng, t_buff *buff)
{
	t_object	*o_array_buffer;
	char		**splitted_line;
	int			i;

	o_array_buffer = (t_object *)ft_memalloc(sizeof(t_object) *
		eng->stats.objects_count);
	i = 0;
	eng->stats.objects_count = 0;
	while (buff->str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff->str[i]);
		if (ft_strcmp(splitted_line[0], "object:") == 0)
			util_create_object(eng, &o_array_buffer[eng->stats.objects_count],
				buff, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	util_find_repeats_in_objects(o_array_buffer, eng->stats.objects_count);
	return (o_array_buffer);
}

void		util_create_object(t_engine *eng, t_object *object,
			t_buff *buff, char **str)
{
	int			vert_count;
	int			str_count;

	util_parsing_error_little_data_check("object", str, 9);
	util_parsing_error_count_handler("object", str, 9);
	object->id = util_int10_data_filler(str[1], 0, 0xFFFF);
	object->portal = util_int10_data_filler(str[2], -1, 0xFFFF);
	object->passble = util_int10_data_filler(str[3], 0, 1);
	object->visible = util_int10_data_filler(str[4], 0, 1);
//	util_find_texture_spread(&object->polies_array->texture_spread, &str[5]);
	if (!ft_strcmp(str[5], "null"))
		object->polies_array->texture = NULL;
	else
		util_find_texture_by_name(&object->polies_array->texture, eng, &str[5], &object->polies_array->texture_spread);
//	util_find_texture_spread(&object->floor_wall_spread, &str[6]);
	util_find_texture_by_name(&object->floor_wall_texture, eng, &str[6], &object->floor_wall_spread);
//	util_find_texture_spread(&object->ceil_wall_spread, &str[7]);
	util_find_texture_by_name(&object->ceil_wall_texture, eng, &str[7], &object->ceil_wall_spread);
	object->polies_count = 1;
	object->polies_array->vertices_count = 2;
	object->polies_array->id = object->id;
	object->polies_array->type = 1;
	object->polies_array->vertices_array =
		(t_point_3d *)ft_memalloc(sizeof(t_point_3d) * 2);
	util_fill_object_with_wallobjects(eng, buff, object);
	str_count = 8;
	vert_count = 0;
	while (str_count < 10)
		object->polies_array->vertices_array[vert_count++] =
			util_get_vertex_from_buff_by_id(ft_atoi(str[str_count++]),
			eng->stats.vertexes_count, buff->vertexes, object->id);
	if (object->polies_array->vertices_array[0].id ==
	object->polies_array->vertices_array[1].id)
		util_parsing_error_repeats("vertexes", "object", object->id);
	eng->stats.objects_count++;
}

t_object	util_get_object_from_buff_by_id(int id, int size,
			t_object *objects, int sector_id)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (objects[i].id == id)
			break ;
		i++;
	}
	if (i == size)
		util_parsing_error_lost_handler("object", id, "sector", sector_id);
	return (objects[i]);
}

void		util_find_repeats_in_objects(t_object *object, int objects_count)
{
	int		j;
	int		i;

	i = 0;
	while (i < objects_count)
	{
		j = 0;
		while (j < objects_count)
		{
			if (object[i].id == object[j].id && i != j)
				util_parsing_error_repeats("objects", "null", object[i].id);
			j++;
		}
		i++;
	}
}

void		util_release_objects_buffer(t_object *object_buff, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		util_release_vertex_buffer(object_buff[i].polies_array->vertices_array);
//		util_release_polies_buffer(object_buff[i].polies_array,
//			object_buff[i].polies_count);
		i++;
	}
	free(object_buff);
}

void		util_parsing_objects_portal(t_engine *eng, t_buff buff)
{
	int		sect_count;
	int		obj_count;
	int		find;

	obj_count = 0;
	while (obj_count < eng->stats.objects_count)
	{
		find = 0;
		sect_count = 0;
		while (sect_count < eng->stats.sectors_count)
		{
			if (buff.objects[obj_count].portal == buff.sectors[sect_count].id
			|| buff.objects[obj_count].portal == -1)
				find = 1;
			sect_count++;
		}
		if (find != 1)
		{
			ft_putendl("Parsing error:");
			ft_putstr("Portal error!\n");
			close_game(PARSING_ERROR);
		}
		obj_count++;
	}
}

void			util_fill_object_with_wallobjects(t_engine *eng, t_buff *buff,
				t_object *object)
{
	int 		wobj_count;
	int 		obj_count;

	wobj_count = 0;
	while (wobj_count < eng->stats.wallobjects_count)
	{
		if (buff->wallobjects[wobj_count].object_id == object->id)
			object->wallobjects_num++;
		wobj_count++;
	}
	if (object->wallobjects_num)
	{
		object->wallobjects_array = (t_wobj *)ft_memalloc(sizeof(t_wobj) *
			object->wallobjects_num);
		wobj_count = 0;
		obj_count = 0;
		while (wobj_count < eng->stats.wallobjects_count)
		{
			if (buff->wallobjects[wobj_count].object_id == object->id)
			{
				object->wallobjects_array[obj_count] =
						buff->wallobjects[wobj_count];
				obj_count++;
			}
			wobj_count++;
		}
	}
}
