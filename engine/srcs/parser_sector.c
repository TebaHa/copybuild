/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/11/12 23:25:52 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_sector		*engine_read_sectors_from_file(t_engine *eng, t_buff buff)
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

void			util_create_sector(t_engine *eng, t_buff buff,
				t_sector *sector, char **str)
{
	int			obj_count;
	int			str_count;

	util_parsing_error_little_data_check("sector", str, 8);
	sector->id = util_int10_data_filler(str[1], 0, 0xFFFF);
	sector->floor = util_int10_data_filler(str[2], -8000, 8000);
	sector->ceil = util_int10_data_filler(str[3], -8000, 8000);
	sector->objects_count = util_int10_data_filler(str[7], 0, 0xFFFF);
	if (sector->objects_count < 3)
		util_parsing_error_little_data("objects", "sector", str);
	sector->sprobjects_count = 0;
	util_parsing_error_count_handler("sector", str, 7 + sector->objects_count);
	sector->objects_array = (t_object *)ft_memalloc(sizeof(t_object)
		* sector->objects_count);
	str_count = 8;
	obj_count = 0;
	sector->opening.range = sector->ceil - sector->floor;
	while (str_count < 8 + sector->objects_count)
		sector->objects_array[obj_count++] =
		util_get_object_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.objects_count, buff.objects, sector->id);
	util_create_sector_sprobjs(eng, sector, str);
	util_find_repeats_in_sector(sector);
	eng->stats.sectors_count++;
}

void			util_create_sector_sprobjs(t_engine *eng,
				t_sector *sector, char **str)
{
	util_find_texture_by_name(&sector->floor_texture, eng, &str[4],
		&sector->floor_spread);
	if (!ft_strcmp(str[5], "null"))
	{
		sector->ceil_visible = false;
		sector->ceil_texture = NULL;
	}
	else
	{
		sector->ceil_visible = true;
		util_find_texture_by_name(&sector->ceil_texture, eng, &str[5],
			&sector->ceil_spread);
	}
	util_read_color(&sector->color, str[6]);
}

void			util_find_sprobjects_repeats_in_sector(t_sector *sector)
{
	int			j;
	int			i;

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

t_sector		*util_get_sector_from_world_by_id(t_engine *eng, int id)
{
	int			sect;

	sect = 0;
	while (sect < eng->world->sectors_count)
	{
		if (eng->world->sectors_array[sect].id == id)
			return (&eng->world->sectors_array[sect]);
		sect++;
	}
	ft_putstr("Parsing error:\nCan't find sector ");
	ft_putnbr(id);
	ft_putstr(" in world!\n");
	close_game(PARSING_ERROR);
	return (NULL);
}
