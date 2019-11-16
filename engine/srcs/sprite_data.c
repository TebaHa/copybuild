/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:20:06 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/16 15:51:38 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	initilize_abs_sprt_sizes(t_player *plr)
{
	plr->arr_sizes = (t_sprts_size **)ft_memalloc(sizeof(t_sprts_size *));
	*plr->arr_sizes = (t_sprts_size *)ft_memalloc(sizeof(t_sprts_size) * 12);
	plr->arr_sizes[0][MEDKIT] = (t_sprts_size){8.f, 40.f, 0.f};
	plr->arr_sizes[0][ARMOR] = (t_sprts_size){8.f, 40.f, 0.f};
	plr->arr_sizes[0][POWER_UP] = (t_sprts_size){10.f, 60.f, 0.f};
	plr->arr_sizes[0][RIFLE_AMMO] = (t_sprts_size){10.f, 40.f, 0.f};
	plr->arr_sizes[0][PLASMA_GUN] = (t_sprts_size){10.f, 40.f, 0.f};
	plr->arr_sizes[0][PLASMA_AMMO] = (t_sprts_size){10.f, 40.f, 0.f};
	plr->arr_sizes[0][BARREL] = (t_sprts_size){15.f, 120.f, 0.f};
	plr->arr_sizes[0][AFRIT] = (t_sprts_size){20.f, 260.f, 0.f};
	plr->arr_sizes[0][CACODEMON] = (t_sprts_size){30.f, 250.f, 10.f};
	plr->arr_sizes[0][IMP] = (t_sprts_size){15.f, 200.f, 0.f};
	plr->arr_sizes[0][JETPACK] = (t_sprts_size){10.f, 40.f, 0.f};
	plr->arr_sizes[0][ENEMY_NUM] = (t_sprts_size){20.f, 20.f, 0.f};
}
