/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_movement_funs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:17:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/21 15:05:54 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	move_player(t_engine *eng, t_player *plr, t_point_2d dd, unsigned sect)
{
	plr->position.x += dd.x;
	plr->position.y += dd.y;
	plr->cursector = sect;
	plr->sinangle = sinf(plr->angle);
	plr->cosangle = cosf(plr->angle);
	check_sprites_in_sector(plr,
	&eng->world->sectors_array[plr->cursector]);
}

void	change_floor(t_engine *eng, int sect, int change)
{
	if (abs(eng->world->sectors_array[sect].floor) < 8000
	&& abs(eng->world->sectors_array[sect].ceil
	- eng->world->sectors_array[sect].floor + change) > 200)
		eng->world->sectors_array[sect].floor += change;
}

void	change_ceil(t_engine *eng, int sect, int change)
{
	if (abs(eng->world->sectors_array[sect].ceil) < 8000
	&& abs(eng->world->sectors_array[sect].floor
	- eng->world->sectors_array[sect].ceil + change) > 200)
		eng->world->sectors_array[sect].ceil += change;
}

void	switch_weapon(t_engine *eng, t_player *plr, int weapon_num)
{
	plr->wpn = eng->weapon[weapon_num];
	plr->wpn->state = W_IDLE;
	plr->frame_num = 0;
}
