/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_fire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 03:03:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/08 19:13:42 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	fire(t_engine *eng, t_player *plr, int state)
{
	plr->shoot = state;
	plr->frame_num = 0;
	if (plr->shoot == 1)
	{
		plr->plr_state = P_FIRE;
		plr->wpn->state = W_FIRE;
	}
	else
	{
		plr->firetime = FIRERATE;
	}
}

void	fire_anim_change(t_engine *eng, t_player *plr)
{
	if (plr->shoot == 1)
	{
		plr->firetime = FIRERATE;
		shoot(eng, plr, 1000);
	}
	if (plr->firetime != 0)
		plr->firetime--;
	if (plr->firetime == 0)
		plr->wpn->state = W_IDLE;
}