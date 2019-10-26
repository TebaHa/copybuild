/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprobject.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_read_sprobjects_from_file(t_engine *eng, t_buff *buff)
{
	char		**splitted_line;
	int			i;

	buff->sprobjects = (t_sprobject *)ft_memalloc(sizeof(t_sprobject) *
		eng->stats.sprobjects_count);
	i = 0;
	eng->stats.sprobjects_count = 0;
	while (buff->str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff->str[i]);
		if (ft_strcmp(splitted_line[0], "sobjct:") == 0)
			util_create_sprobject(eng, &buff->sprobjects[
				eng->stats.sprobjects_count], buff, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	util_fill_sector_with_sprobjects(eng, buff);
}

void			util_create_sprobject(t_engine *eng, t_sprobject *sprobject,
				t_buff *buff, char **str)
{
	t_sector	*sector;
	util_parsing_error_little_data_check("sprite object", str, 4);
	util_parsing_error_count_handler("sprite object", str, 4);
	sprobject->id = util_int10_data_filler(str[1], 0, 5000);
	sprobject->angle = util_int10_data_filler(str[2], 0, 360);
	if (ft_atoi(str[3]) < 0 || ft_atoi(str[3]) > ENEMY_NUM)
		util_parsing_error_cant_find("texture from sprobject", ft_atoi(str[3]));
	sprobject->enum_type = util_int10_data_filler(str[3], 0, ENEMY_NUM - 1);
	sprobject->type = eng->enemy[ft_atoi(str[3])];
	sprobject->position = util_get_vertex_from_buff_by_id(ft_atoi(str[4]),
		eng->stats.vertexes_count, buff->vertexes, sprobject->id);
	if ((sprobject->sector_id = engine_object_get_sector(eng->world,
	sprobject->position, 0)) == -1)
	{
		ft_putstr("Parsing error:\nSprobject ");
		ft_putnbr(sprobject->id);
		ft_putstr(" not in any sector!\n");
		close_game(PARSING_ERROR);
	}
	sector = util_get_sector_from_world_by_id(eng, sprobject->sector_id);
	sector->sprobjects_count++;
	sprobject->state = E_IDLE;
	eng->stats.sprobjects_count++;
}

void			util_fill_sector_with_sprobjects(t_engine *eng, t_buff *buff)
{
	int 		sect_count;
	int 		sprobj_count;
	int 		sprobj_count_global;

	sect_count = 0;
	while (sect_count < eng->world->sectors_count)
	{
		if (eng->world->sectors_array[sect_count].sprobjects_count)
		{
			eng->world->sectors_array[sect_count].sprobjects_array =
			(t_sprobject *)ft_memalloc(sizeof(t_sprobject) *
			eng->world->sectors_array[sect_count].sprobjects_count);
			sprobj_count_global = 0;
			sprobj_count = 0;
			while (sprobj_count_global < eng->stats.sprobjects_count)
			{
				if (eng->world->sectors_array[sect_count].id ==
				buff->sprobjects[sprobj_count_global].sector_id)
				{
					eng->world->sectors_array[sect_count].sprobjects_array[sprobj_count] =
					buff->sprobjects[sprobj_count_global];
					sprobj_count++;
				}
				sprobj_count_global++;
			}
		}
		sect_count++;
	}
}
