/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/22 20:13:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_read_plr_pos(t_engine *eng, t_player *plr, t_buff buff)
{
	if (eng->stats.players_count == 1)
	{
		engine_read_plr_pos_from_file(eng, plr, buff);
	}
	else if (eng->stats.players_count > 1)
		util_parsing_error_lot_of("players");
	engine_check_plr_pos(eng->world, plr);
}

void		engine_read_plr_pos_from_file(t_engine *eng, t_player *plr,
			t_buff buff)
{
	char		**splitted_line;
	int			i;

	i = 0;
	while (buff.str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
		if (ft_strcmp(splitted_line[0], "player:") == 0)
			util_create_player(eng, plr, buff, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
}

void		util_create_player(t_engine *eng, t_player *plr, t_buff buff,
			char **str)
{
	t_point_3d		position;

	util_parsing_error_count_handler("player", str, 2);
	plr->angle = util_int10_data_filler(str[1], 0, 360);
	position = util_get_vertex_from_buff_by_id(ft_atoi(str[2]),
		eng->stats.vertexes_count, buff.vertexes, 99);
	plr->position.x = position.x;
	plr->position.y = position.y;
	plr->position.z = position.z;
}

void		engine_check_plr_pos(t_world *world, t_player *plr)
{
	t_point_3d	temp;

	temp.x = plr->position.x - 1;
	temp.y = plr->position.y - 1;
	while (temp.x <= plr->position.x + 1)
	{
		while (temp.y <= plr->position.y + 1)
		{
			if ((plr->start_sector = engine_object_get_sector(world, temp, 0))
			== -1)
				util_parsing_error_player_outside("outside of");
			temp.y++;
		}
		temp.x++;
	}
	engine_check_plr_vertical_pos(world, plr);
}
