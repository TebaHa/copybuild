/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 00:57:34 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/19 05:31:15 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		parser_engine(t_engine *eng, t_player *plr)
{
	engine_create_engine_resources(eng);
	engine_create_world_from_file(eng, plr, eng->map_name);
	plr->wpn = eng->weapon[1];
	plr->cursector = 0;
}

void		engine_create_engine_resources(t_engine *eng)
{
	engine_find_background(eng);
	eng_create_hud(eng);
	eng_create_weapons(eng);
	eng_create_items(eng);
	eng_create_enemies(eng);
	eng_create_buttons(eng);
	eng_create_background_music(eng);
}

void		engine_create_world_from_file(t_engine *eng, t_player *plr,
			char *filename)
{
	t_buff		buff;

	buff.str = engine_read_level_file(filename);
	engine_preparser(eng, buff.str);
	buff.vertexes = engine_read_vertexes_from_file(eng, buff.str);
	buff.wallobjects = engine_read_wallobjects_from_file(eng, buff);
	buff.objects = engine_read_objects_from_file(eng, &buff);
	buff.sectors = engine_read_sectors_from_file(eng, buff);
	util_parsing_objects_portal(eng, buff);
	engine_read_world_from_file(eng, buff);
	util_parsing_double_portal(eng);
	engine_read_sprobjects_from_file(eng, &buff);
	engine_read_plr_pos(eng, plr, buff);
	util_release_read_buffers(&buff);
}

void		engine_preparser(t_engine *eng, char **buff)
{
	eng->stats.vertexes_count = 0;
	eng->stats.objects_count = 0;
	eng->stats.sprobjects_count = 0;
	eng->stats.wallobjects_count = 0;
	eng->stats.sectors_count = 0;
	eng->stats.worlds_count = 0;
	eng->stats.players_count = 0;
	engine_count_all_from_file(&eng->stats, buff);
	if (!eng->stats.worlds_count)
		util_parsing_error_not_enough("worlds");
	if (!eng->stats.sectors_count)
		util_parsing_error_not_enough("sectors");
	if (!eng->stats.objects_count)
		util_parsing_error_not_enough("objects");
	if (!eng->stats.vertexes_count)
		util_parsing_error_not_enough("vertexes");
}

void		engine_count_all_from_file(t_stats *stats, char **buff)
{
	int		i;

	i = 0;
	while (buff[i])
	{
		if (ft_strwcmp(buff[i], "vertex:") == 0)
			stats->vertexes_count++;
		else if (ft_strwcmp(buff[i], "object:") == 0)
			stats->objects_count++;
		else if (ft_strwcmp(buff[i], "sector:") == 0)
			stats->sectors_count++;
		else if (ft_strwcmp(buff[i], "sprite:") == 0)
			stats->skins_count++;
		else if (ft_strwcmp(buff[i], "sobjct:") == 0)
			stats->sprobjects_count++;
		else if (ft_strwcmp(buff[i], "wobjct:") == 0)
			stats->wallobjects_count++;
		else if (ft_strwcmp(buff[i], "world:") == 0)
			stats->worlds_count++;
		else if (ft_strwcmp(buff[i], "player:") == 0)
			stats->players_count++;
		i++;
	}
}
