/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_movement_funs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:17:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/03 17:24:54 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	move_player(t_engine *eng, t_player *plr, t_point_2d dd)
{
	int			i;
	t_sector	*s;

	i = 0;
	s = &eng->world->sectors_array[plr->cursector];
	while (i < s->objects_count)
	{
		if (s->objects_array[i].portal >= 0 &&
		line_intersection_check((t_line_2d){(t_point_2d){
		plr->position.x, plr->position.y
		},
		(t_point_2d){
		plr->position.x + dd.x, plr->position.y + dd.y
		}},(t_line_2d){(t_point_2d){
		s->objects_array[i].polies_array[0].vertices_array[0].x,
		s->objects_array[i].polies_array[0].vertices_array[0].y
		},(t_point_2d){
		s->objects_array[i].polies_array[0].vertices_array[1].x,
		s->objects_array[i].polies_array[0].vertices_array[1].y
		}}))
		{
			plr->cursector = s->objects_array[i].portal;
			break ;
		}
		i++;
	}
	plr->position.x += dd.x;
	plr->position.y += dd.y;
	plr->sinangle = sinf(plr->angle);
	plr->cosangle = cosf(plr->angle);
	check_sprites_in_sector(plr,
	&eng->world->sectors_array[plr->cursector]);
}

void	change_floor(t_engine *eng, int sect, int change)
{

	if (abs(eng->world->sectors_array[sect].floor) < 8000
	&& abs(eng->world->sectors_array[sect].floor
	- eng->world->sectors_array[sect].ceil + change) > 200)
		eng->world->sectors_array[sect].floor += change;
}

void	change_ceil(t_engine *eng, int sect, int change)
{
	if (abs(eng->world->sectors_array[sect].ceil) < 8000
	&& abs(eng->world->sectors_array[sect].ceil
	- eng->world->sectors_array[sect].floor + change) > 200)
		eng->world->sectors_array[sect].ceil += change;
}

void	switch_weapon(t_engine *eng, t_player *plr, int weapon_num)
{
	plr->wpn = eng->weapon[weapon_num];
	plr->wpn->state = W_IDLE;
	plr->frame_num = 0;
}
