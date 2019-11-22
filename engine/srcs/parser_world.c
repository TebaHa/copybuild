/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:12:50 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/25 08:42:27 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_read_world_from_file(t_engine *eng, t_buff buff)
{
	char	**splitted_line;
	int		i;

	i = 0;
	while (buff.str[i])
	{
		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
		if (ft_strcmp(splitted_line[0], "world:") == 0)
		{
			util_create_world(eng, &eng->world, buff, splitted_line);
			if (eng->world->sectors_count > eng->stats.sectors_count)
				util_parsing_error_not_enough("sectors");
		}
		util_release_char_matrix(splitted_line);
		i++;
	}
}

t_sector	*util_get_sector_from_buff_by_id(int id, int size,
			t_sector *sector, int world_id)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (sector[i].id == id)
			break ;
		i++;
	}
	if (i == size)
		util_parsing_error_lost_handler("sector", id, "world", world_id);
	return (&sector[i]);
}

void		util_create_world(t_engine *eng, t_world **world,
			t_buff buff, char **str)
{
	int		sect_count;
	int		str_count;

	*world = (t_world *)ft_memalloc(sizeof(t_world));
	(*world)->id = util_int10_data_filler(str[1], 0, 0xFFFF);
	(*world)->sectors_count = util_int10_data_filler(str[2], 0, 0xFFFF);
	if (((*world)->sectors_count) != eng->stats.sectors_count)
		util_parsing_error_not_enough("sectors");
	if (!(*world)->sectors_count)
		util_parsing_error_little_data("sectors", "world", str);
	util_parsing_error_count_handler("world", str, 2 + (*world)->sectors_count);
	(*world)->sectors_array = (t_sector *)ft_memalloc(sizeof(t_sector)
		* (*world)->sectors_count);
	str_count = 3;
	sect_count = 0;
	while (str_count < 3 + (*world)->sectors_count)
		(*world)->sectors_array[sect_count++] =
			*util_get_sector_from_buff_by_id(ft_atoi(str[str_count++]),
			eng->stats.sectors_count, buff.sectors, (*world)->id);
	util_find_repeats_in_world(*world);
	(*world)->world_box = (t_sector *)ft_memalloc(sizeof(t_sector));
}

void		util_find_repeats_in_world(t_world *world)
{
	int		j;
	int		i;

	i = 0;
	while (i < world->sectors_count)
	{
		j = 0;
		while (j < world->sectors_count)
		{
			if (i != j)
				if (world->sectors_array[i].id == world->sectors_array[j].id)
					util_parsing_error_repeats("sectors", "world", world->id);
			j++;
		}
		i++;
	}
}

void		util_release_world(t_world *world)
{
	util_release_sectors_buffer(world->sectors_array, world->sectors_count);
	free(world);
}
