/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/18 20:26:30 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_sector	*engine_read_sectors_from_file(t_engine *eng, t_buff buff)
{
	t_sector	*s_array_buffer;
	char		**splitted_line;
	int			i;

	s_array_buffer = (t_sector *)ft_memalloc(sizeof(t_sector) *
		eng->stats.sectors_count);
	i = 0;
	eng->stats.sectors_count = 0;
	while (buff.str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
		if (ft_strcmp(splitted_line[0], "sector:") == 0)
			util_create_sector(eng, buff,
			&s_array_buffer[eng->stats.sectors_count], splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (s_array_buffer);
}

void		util_create_sector(t_engine *eng, t_buff buff,
			t_sector *sector, char **str)
{
	int			obj_count;
	int			str_count;

	util_int10_data_filler(&sector->id, str[1], 0, 0xFFFF);
	util_int10_data_filler(&sector->floor, str[2], -8000, 8000);
	util_int10_data_filler(&sector->ceil, str[3], -8000, 8000);
	util_find_texture_by_name(&sector->floor_texture, eng, str[4]);
	util_find_texture_by_name(&sector->ceil_texture, eng, str[5]);
	util_int10_data_filler(&sector->objects_count, str[7], 0, 0xFFFF);
	if (sector->objects_count < 3)
		util_parsing_error_little_data("objects", "sector", str);
	util_int10_data_filler(&sector->sprobjects_count, str[8], 0, 0xFFFF);
	util_parsing_error_count_handler("sector", str, 8 + sector->objects_count
		+ sector->sprobjects_count);
	sector->objects_array = (t_object *)ft_memalloc(sizeof(t_object)
		* sector->objects_count);
	str_count = 9;
	obj_count = 0;
	while (str_count < 9 + sector->objects_count)
		sector->objects_array[obj_count++] =
		util_get_object_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.objects_count, buff.objects, sector->id);
	util_create_sector_sprobjs(eng, buff, sector, str);
	util_find_repeats_in_sector(sector);
	eng->stats.sectors_count++;
}

void		util_create_sector_sprobjs(t_engine *eng, t_buff buff,
			t_sector *sector, char **str)
{
	int			sprobj_count;
	int			str_count;

	util_read_color(&sector->color, str[6]);
	sector->dist = (float *)ft_memalloc(sizeof(float)
		* sector->objects_count);
	sector->order = (int *)ft_memalloc(sizeof(int) * sector->objects_count);
	sector->sprobjects_array = (t_sprobject *)ft_memalloc(sizeof(t_sprobject)
		* sector->sprobjects_count);
	str_count = 9 + sector->objects_count;
	sprobj_count = 0;
	while (str_count < 9 + sector->objects_count + sector->sprobjects_count)
		sector->sprobjects_array[sprobj_count++] =
		util_get_sprobject_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.sprobjects_count, buff.sprobjects, sector->id);
}

void		util_find_repeats_in_sector(t_sector *sector)
{
	int		j;
	int		i;

	i = 0;
	while (i < sector->objects_count)
	{
		j = 0;
		while (j < sector->objects_count)
		{
			if (i != j)
			{
				if (sector->objects_array[i].id == sector->objects_array[j].id)
					util_parsing_error_repeats("objects", "sector", sector->id);
				if (sector->objects_array[i].polies_array[0].id ==
					sector->objects_array[j].polies_array[0].id)
					util_parsing_error_repeats("polies", "sector", sector->id);
			}
			j++;
		}
		i++;
	}
	util_find_sprobjects_repeats_in_sector(sector);
}

void		util_find_sprobjects_repeats_in_sector(t_sector *sector)
{
	int		j;
	int		i;

	i = 0;
	while (i < sector->sprobjects_count)
	{
		j = 0;
		while (j < sector->sprobjects_count)
		{
			if (sector->sprobjects_array[i].id ==
				sector->sprobjects_array[j].id && i != j)
				util_parsing_error_repeats("sprobjects", "sector", sector->id);
			j++;
		}
		i++;
	}
}
