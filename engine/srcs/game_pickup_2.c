/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_pickup_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:54:05 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 15:56:17 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_bool		apply_sprite_obj_help(t_player *plr, t_sprobject *sobj)
{
	t_bool	picked;

	if (sobj->enum_type == PLASMA_AMMO)
	{
		if (ft_strcmp(plr->wpn->name, "Plazma gun") == 0)
			picked = modify_players_stat(&plr->wpn->ammo, 10, 50);
	}
	else if (sobj->enum_type == RIFLE_AMMO)
	{
		if (ft_strcmp(plr->wpn->name, "Rifle") == 0)
			picked = modify_players_stat(&plr->wpn->ammo, 25, 300);
	}
	return (picked);
}
