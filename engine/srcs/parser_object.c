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

t_object	*engine_read_objects_from_file(t_engine *eng, t_buff buff)
{
	t_object	*o_array_buffer;
	char		**splitted_line;
	int			i;

	o_array_buffer = (t_object *)ft_memalloc(sizeof(t_object) *
		eng->stats.objects_count);
	i = 0;
	eng->stats.objects_count = 0;
	while (buff.str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
		if (ft_strcmp(splitted_line[0], "object:") == 0)
			util_create_object(eng, &o_array_buffer[eng->stats.objects_count],
				buff.polies, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (o_array_buffer);
}

void		util_create_object(t_engine *eng, t_object *object,
			t_polygone *polygone_array, char **str)
{
	int			pol_count;
	int			str_count;

	util_int10_data_filler(&object->id, str[1]);
	util_int10_data_filler(&object->portal, str[2]);
	util_int10_data_filler(&object->passble, str[3]);
	util_int10_data_filler(&object->visible, str[4]);
	util_find_texture_by_name(&object->floor_wall_texture, eng, str[5]);
	util_find_texture_by_name(&object->ceil_wall_texture, eng, str[6]);
	util_int10_data_filler(&object->polies_count, str[7]);
	if (!object->polies_count)
		util_parsing_error_little_data("polies", "object", str);
	util_parsing_error_count_handler("object", str, 7 + object->polies_count);
	object->polies_array = (t_polygone *)ft_memalloc(sizeof(t_polygone)
		* object->polies_count);
	str_count = 8;
	pol_count = 0;
	while (str_count < 8 + object->polies_count)
		object->polies_array[pol_count++] =
			util_get_polygone_from_buff_by_id(ft_atoi(str[str_count++]),
			eng->stats.polies_count, polygone_array, object->id);
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

void		util_release_objects_buffer(t_object *object_buff, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		util_release_polies_buffer(object_buff[i].polies_array,
			object_buff[i].polies_count);
		i++;
	}
	free(object_buff);
}
