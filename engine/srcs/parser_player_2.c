/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_check_plr_vertical_pos(t_world *world, t_player *plr)
{
//	if (world->sectors_array[plr->start_sector].floor > plr->position.z)
//		util_parsing_error_player_outside("under");
//	if (world->sectors_array[plr->start_sector].ceil < plr->position.z)
//		util_parsing_error_player_outside("above");
	t_sector	*plr_sect;

	plr_sect = util_get_sector_from_world_by_id(world, plr->start_sector);
	if (plr_sect->floor > plr->position.z)
		util_parsing_error_player_outside("under");
	if (plr_sect->ceil < plr->position.z)
		util_parsing_error_player_outside("above");
}

void		util_parsing_error_player_outside(char *position)
{
	ft_putendl("Parsing error:");
	ft_putstr("Player ");
	ft_putstr(position);
	ft_putendl(" map!");
	close_game(PARSING_ERROR);
}
