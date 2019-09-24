/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:14:57 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/23 20:49:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

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

void 		eng_create_afrit(t_engine *eng)
{
	t_enemy	*afrit;

	afrit = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	afrit->id = AFRIT;
	afrit->name = ft_strdup("Afrit");
	afrit->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "afrit_idle");
//	afrit->anmtn[E_RUN] = util_create_sprite_by_name(eng, "afrit_run");
	afrit->anmtn[E_RUN] = afrit->anmtn[E_IDLE];
//	afrit->anmtn[E_FIRE] = util_create_sprite_by_name(eng, "afrit_fire");
	afrit->anmtn[E_FIRE] = afrit->anmtn[E_IDLE];
	afrit->anmtn[E_HURT] = util_create_sprite_by_name(eng, "afrit_hurt");
	afrit->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "afrit_dead");
	eng->enemy[AFRIT] = afrit;
}
