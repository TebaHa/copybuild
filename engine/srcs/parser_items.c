/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:29:13 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/29 16:29:13 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		eng_create_items(t_engine *eng)
{
	eng_create_medkit(eng);
	eng_create_armor(eng);
	eng_create_powerup(eng);
	eng_create_rifle_ammo(eng);
	eng_create_plasma_ammo(eng);
	eng_create_plasma_gun(eng);
	eng_create_barrel(eng);
}

void		eng_create_medkit(t_engine *eng)
{
	t_enemy	*medkit;

	medkit = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	medkit->id = MEDKIT;
	medkit->name = ft_strdup("Medkit");
	medkit->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "medkit");
	medkit->anmtn[E_RUN] = medkit->anmtn[E_IDLE];
	medkit->anmtn[E_FIRE] = medkit->anmtn[E_IDLE];
	medkit->anmtn[E_HURT] = medkit->anmtn[E_IDLE];
	medkit->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "empty_place");
	eng->enemy[MEDKIT] = medkit;
}

void		eng_create_armor(t_engine *eng)
{
	t_enemy	*armor;

	armor = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	armor->id = ARMOR;
	armor->name = ft_strdup("Armor");
	armor->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "armor");
	armor->anmtn[E_RUN] = armor->anmtn[E_IDLE];
	armor->anmtn[E_FIRE] = armor->anmtn[E_IDLE];
	armor->anmtn[E_HURT] = armor->anmtn[E_IDLE];
	armor->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "empty_place");
	eng->enemy[ARMOR] = armor;
}

void		eng_create_powerup(t_engine *eng)
{
	t_enemy	*powerup;

	powerup = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	powerup->id = POWER_UP;
	powerup->name = ft_strdup("Power up");
	powerup->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "power_up");
//	if (powerup->anmtn[E_IDLE]->a_state == ANIMATE)
//		powerup->anmtn[E_IDLE]->a_state = PENDULUM;
	powerup->anmtn[E_RUN] = powerup->anmtn[E_IDLE];
	powerup->anmtn[E_FIRE] = powerup->anmtn[E_IDLE];
	powerup->anmtn[E_HURT] = powerup->anmtn[E_IDLE];
	powerup->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "empty_place");
	eng->enemy[POWER_UP] = powerup;
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

void 		eng_create_barrel(t_engine *eng)
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
