/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:14:57 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/28 16:10:19 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		eng_create_enemies(t_engine *eng)
{
	eng_create_afrit(eng);
	eng_create_cacodemon(eng);
	eng_create_imp(eng);
}

void		eng_create_afrit(t_engine *eng)
{
	t_enemy	*afrit;

	afrit = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	afrit->id = AFRIT;
	afrit->name = ft_strdup("Afrit");
	afrit->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "afrit_idle");
	afrit->anmtn[E_IDLE]->a_state = CYCLE;
	afrit->anmtn[E_RUN] = util_create_sprite_by_name(eng, "afrit_run");
	afrit->anmtn[E_RUN]->a_state = CYCLE;
	afrit->anmtn[E_FIRE] = util_create_sprite_by_name(eng, "afrit_fire");
	afrit->anmtn[E_HURT] = util_create_sprite_by_name(eng, "afrit_hurt");
	afrit->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "afrit_dead");
	eng->enemy[AFRIT] = afrit;
}

void		eng_create_cacodemon(t_engine *eng)
{
	t_enemy	*demon;

	demon = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	demon->id = CACODEMON;
	demon->name = ft_strdup("Cacodemon");
	demon->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "cacodemon_idle");
	demon->anmtn[E_RUN] = demon->anmtn[E_IDLE];
	demon->anmtn[E_FIRE] = util_create_sprite_by_name(eng, "cacodemon_fire");
	demon->anmtn[E_HURT] = util_create_sprite_by_name(eng, "cacodemon_hurt");
	demon->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "cacodemon_dead");
	eng->enemy[CACODEMON] = demon;
}

void		eng_create_imp(t_engine *eng)
{
	t_enemy	*imp;

	imp = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	imp->id = IMP;
	imp->name = ft_strdup("Imp");
	imp->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "imp_idle");
	imp->anmtn[E_RUN] = util_create_sprite_by_name(eng, "imp_run");
	imp->anmtn[E_RUN]->a_state = CYCLE;
	imp->anmtn[E_FIRE] = util_create_sprite_by_name(eng, "imp_fire");
	imp->anmtn[E_HURT] = util_create_sprite_by_name(eng, "imp_hurt");
	imp->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "imp_dead");
	eng->enemy[IMP] = imp;
}
