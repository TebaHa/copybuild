/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_items_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:29:13 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/10 01:05:10 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		eng_create_barrel(t_engine *eng)
{
	t_enemy	*barrel;

	barrel = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	barrel->id = BARREL;
	barrel->name = ft_strdup("Barrel");
	barrel->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "barrel_idle");
	barrel->anmtn[E_RUN] = barrel->anmtn[E_IDLE];
	barrel->anmtn[E_FIRE] = barrel->anmtn[E_IDLE];
	barrel->anmtn[E_HURT] = util_create_sprite_by_name(eng, "barrel_hit");
	barrel->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "barrel_destroyed");
	eng->enemy[BARREL] = barrel;
}

void		eng_create_rifle_ammo(t_engine *eng)
{
	t_enemy	*ammo;

	ammo = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	ammo->id = RIFLE_AMMO;
	ammo->name = ft_strdup("Rifle ammo");
	ammo->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "rifle_ammo");
	ammo->anmtn[E_RUN] = ammo->anmtn[E_IDLE];
	ammo->anmtn[E_FIRE] = ammo->anmtn[E_IDLE];
	ammo->anmtn[E_HURT] = ammo->anmtn[E_IDLE];
	ammo->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "empty_place");
	ammo->death_sound = sound_init("pickup_ammo");
	eng->enemy[RIFLE_AMMO] = ammo;
}

void		eng_create_plasma_ammo(t_engine *eng)
{
	t_enemy	*ammo;

	ammo = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	ammo->id = PLASMA_AMMO;
	ammo->name = ft_strdup("Plasma ammo");
	ammo->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "plasma_ammo");
	ammo->anmtn[E_RUN] = ammo->anmtn[E_IDLE];
	ammo->anmtn[E_FIRE] = ammo->anmtn[E_IDLE];
	ammo->anmtn[E_HURT] = ammo->anmtn[E_IDLE];
	ammo->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "empty_place");
	ammo->death_sound = sound_init("pickup_ammo");
	eng->enemy[PLASMA_AMMO] = ammo;
}

void		eng_create_plasma_gun(t_engine *eng)
{
	t_enemy	*plasma;

	plasma = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	plasma->id = PLASMA_GUN;
	plasma->name = ft_strdup("Plasma gun");
	plasma->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "plasma_gun");
	plasma->anmtn[E_RUN] = plasma->anmtn[E_IDLE];
	plasma->anmtn[E_FIRE] = plasma->anmtn[E_IDLE];
	plasma->anmtn[E_HURT] = plasma->anmtn[E_IDLE];
	plasma->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "empty_place");
	eng->enemy[PLASMA_GUN] = plasma;
}
