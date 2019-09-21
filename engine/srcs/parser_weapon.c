/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:44:08 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/21 19:55:58 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void 	eng_create_rifle(t_engine *eng)
{
	eng->weapon->id = 0;
	eng->weapon->name = ft_strdup("Rifle");
	eng->weapon->ammo = 30;
	eng->weapon->max_ammo = 30;
	eng->weapon->containers = 0;
	eng->weapon->state = W_IDLE;
	eng->weapon->anmtn[W_IDLE] = util_get_hud_sprite_from_buff("rifle_idle",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_RUN] = util_get_hud_sprite_from_buff("rifle_run",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_FIRE] = util_get_hud_sprite_from_buff("rifle_fire",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_NO_AMMO] = util_get_hud_sprite_from_buff("rifle_no_ammo",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_RELOAD] = util_get_hud_sprite_from_buff("rifle_reload",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_HURT] = util_get_hud_sprite_from_buff("rifle_hurt",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->bullet_hole = util_get_sprite_from_buff_by_name("bullet_hole",
		*eng->sprites_buffer, eng->stats.sprites_count);
}

void 	eng_create_plazma(t_engine *eng)
{
	eng->weapon->id = 0;
	eng->weapon->name = ft_strdup("Plazma gun");
	eng->weapon->ammo = 30;
	eng->weapon->max_ammo = 30;
	eng->weapon->containers = 0;
	eng->weapon->state = W_IDLE;
	eng->weapon->anmtn[W_IDLE] = util_get_hud_sprite_from_buff("rifle_idle",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_RUN] = util_get_hud_sprite_from_buff("rifle_run",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_FIRE] = util_get_hud_sprite_from_buff("rifle_fire",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_NO_AMMO] = util_get_hud_sprite_from_buff("rifle_no_ammo",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_RELOAD] = util_get_hud_sprite_from_buff("rifle_reload",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->anmtn[W_HURT] = util_get_hud_sprite_from_buff("rifle_hurt",
		*eng->sprites_buffer, eng->stats.sprites_count);
	eng->weapon->bullet_hole = util_get_sprite_from_buff_by_name("bullet_hole",
		*eng->sprites_buffer, eng->stats.sprites_count);
}
