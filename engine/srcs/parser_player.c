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
			if (engine_object_get_sector(world, temp, 0) == -1)
				util_parsing_error_player_outside();
			temp.y++;
		}
		temp.x++;
	}
}

void		util_parsing_error_player_outside(void)
{
	ft_putendl("Parsing error:");
	ft_putendl("Player outside of map!");
	exit(PARSING_ERROR);
}
