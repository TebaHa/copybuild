/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:44:08 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/20 22:56:41 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			eng_create_weapons(t_engine *eng)
{
	eng_create_rifle(eng);
	eng_create_plasma(eng);
}

void			eng_create_rifle(t_engine *eng)
{
	t_weapon	*rifle;

	rifle = (t_weapon *)ft_memalloc(sizeof(t_weapon));
	rifle->id = RIFLE;
	rifle->name = ft_strdup("Rifle");
	rifle->ammo = 30;
	rifle->max_ammo = 30;
	rifle->containers = 0;
	rifle->state = W_IDLE;
	rifle->cooldown = 0;
	rifle->bullet_hole = util_create_sprite_by_name(eng, "bullet_hole");
	rifle->anmtn[W_IDLE] = util_create_sprite_by_name(eng, "rifle_idle");
	rifle->anmtn[W_RUN] = rifle->anmtn[W_IDLE];
	rifle->anmtn[W_FIRE] = util_create_sprite_by_name(eng, "rifle_fire");
	rifle->anmtn[W_FIRE]->frames_delay = 7;
	rifle->anmtn[W_NO_AMMO] = util_create_sprite_by_name(eng, "rifle_no_ammo");
	rifle->anmtn[W_RELOAD] = rifle->anmtn[W_IDLE];
	rifle->anmtn[W_HURT] = rifle->anmtn[W_IDLE];
	rifle->shot_sound = sound_init("rifle_shot_single");
	rifle->cooldown = 4;
	eng->weapon[RIFLE] = rifle;
	eng->weapon[RIFLE]->next = eng->weapon[PLASMA];
	eng->weapon[RIFLE]->prev = eng->weapon[PLASMA];
}

void			eng_create_plasma(t_engine *eng)
{
	t_weapon	*plasma;

	plasma = (t_weapon *)ft_memalloc(sizeof(t_weapon));
	plasma->id = PLASMA;
	plasma->name = ft_strdup("Plazma gun");
	plasma->ammo = 5;
	plasma->max_ammo = 5;
	plasma->containers = 0;
	plasma->state = W_IDLE;
	plasma->bullet_hole = util_create_sprite_by_name(eng, "plasma_hole");
	plasma->anmtn[W_IDLE] = util_create_sprite_by_name(eng, "plasma_idle");
	plasma->anmtn[W_RUN] = plasma->anmtn[W_IDLE];
	plasma->anmtn[W_FIRE] = util_create_sprite_by_name(eng, "plasma_fire");
	plasma->anmtn[W_NO_AMMO] =
		util_create_sprite_by_name(eng, "plasma_no_ammo");
	plasma->anmtn[W_RELOAD] = plasma->anmtn[W_IDLE];
	plasma->anmtn[W_HURT] = plasma->anmtn[W_IDLE];
	plasma->shot_sound = sound_init("plasma_shot_single");
	plasma->cooldown = 40;
	eng->weapon[PLASMA] = plasma;
	eng->weapon[PLASMA]->next = eng->weapon[RIFLE];
	eng->weapon[PLASMA]->prev = eng->weapon[RIFLE];
}
