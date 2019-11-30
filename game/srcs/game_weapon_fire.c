/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_fire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 03:03:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/28 19:46:21 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	fire(t_player *plr, int state)
{
	plr->shoot = state;
	plr->frame_num = 0;
	if (plr->shoot)
	{
		plr->plr_state = P_FIRE;
		plr->wpn->state = W_FIRE;
	}
}

void	fire_anim_change(t_engine *eng, t_player *plr)
{
	if (plr->shoot && plr->wpn->ammo > 0)
	{
		if ((plr->firetime % (plr->wpn->cooldown * 2)) == 0)
		{
			sound_shoot(plr);
			shoot(eng, plr, 1000);
			plr->wpn->ammo--;
		}
	}
	else if (plr->plr_state != P_IDLE || plr->wpn->state != W_IDLE)
	{
		plr->plr_state = P_IDLE;
		plr->frame_num = 0;
		plr->wpn->state = W_IDLE;
		plr->firetime = 0;
	}
	plr->firetime++;
}
