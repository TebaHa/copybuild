/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_fire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 03:03:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 16:59:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	fire(t_engine *eng, t_player *plr, int state)
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
	if (plr->shoot)
	{
		if ((plr->firetime % plr->wpn->cooldown) == 0)
			sound_shoot(plr);
		if ((plr->firetime % (plr->wpn->cooldown)) == 0)
			shoot(eng, plr, 1000);
	}
	else
	{
		plr->plr_state = P_IDLE;
		plr->wpn->state = W_IDLE;
	}
	plr->firetime++;
}
