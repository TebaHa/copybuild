/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

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

void		engine_check_plr_vertical_pos(t_world *world, t_player *plr)
{
	if (world->sectors_array[plr->start_sector].floor > plr->position.z)
		util_parsing_error_player_outside("under");
	if (world->sectors_array[plr->start_sector].ceil < plr->position.z)
		util_parsing_error_player_outside("above");
}

void		util_parsing_error_player_outside(char *position)
{
	ft_putendl("Parsing error:");
	ft_putstr("Player ");
	ft_putstr(position);
	ft_putendl(" map!");
	exit(PARSING_ERROR);
}
