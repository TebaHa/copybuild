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
	afrit->rotatable = ROTATABLE;
	afrit->anmtn_360[E_IDLE] = util_create_sprite_360_by_name(eng,
			"afrit_idle");
	afrit->anmtn_360[E_HURT] = util_create_sprite_360_by_name(eng,
			"afrit_hurt");
	afrit->anmtn_360[E_FIRE] = util_create_sprite_360_by_name(eng,
			"afrit_fire");
	afrit->anmtn_360[E_DEAD] = util_create_sprite_0_by_name(eng,
			"afrit_dead");
	afrit->shot = util_create_sprite_by_name(eng, "afrit_shot");
	afrit->anmtn_360[E_RUN] = afrit->anmtn_360[E_IDLE];
	afrit->anmtn[E_IDLE] = afrit->anmtn_360[E_IDLE][EA_000];
	afrit->anmtn[E_HURT] = afrit->anmtn_360[E_HURT][EA_000];
	afrit->anmtn[E_FIRE] = afrit->anmtn_360[E_FIRE][EA_000];
	afrit->anmtn[E_DEAD] = afrit->anmtn_360[E_DEAD][EA_000];
	afrit->anmtn[E_RUN] = afrit->anmtn_360[E_RUN][EA_000];
	eng->enemy[AFRIT] = afrit;
}

void		eng_create_cacodemon(t_engine *eng)
{
	t_enemy	*demon;

	demon = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	demon->id = CACODEMON;
	demon->name = ft_strdup("Cacodemon");
	demon->rotatable = ROTATABLE;
	demon->anmtn_360[E_IDLE] = util_create_sprite_360_by_name(eng,
			"cacodemon_idle");
	demon->anmtn_360[E_HURT] = util_create_sprite_360_by_name(eng,
			"cacodemon_hurt");
	demon->anmtn_360[E_FIRE] = util_create_sprite_360_by_name(eng,
			"cacodemon_fire");
	demon->anmtn_360[E_DEAD] = util_create_sprite_0_by_name(eng,
			"cacodemon_dead");
	demon->shot = util_create_sprite_by_name(eng, "empty_place");
	demon->anmtn_360[E_RUN] = demon->anmtn_360[E_IDLE];
	demon->anmtn[E_IDLE] = demon->anmtn_360[E_IDLE][EA_000];
	demon->anmtn[E_FIRE] = demon->anmtn_360[E_FIRE][EA_000];
	demon->anmtn[E_HURT] = demon->anmtn_360[E_HURT][EA_000];
	demon->anmtn[E_DEAD] = demon->anmtn_360[E_DEAD][EA_000];
	demon->anmtn[E_RUN] = demon->anmtn_360[E_RUN][EA_000];
	eng->enemy[CACODEMON] = demon;
}

void		eng_create_imp(t_engine *eng)
{
	t_enemy	*imp;

	imp = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	imp->id = IMP;
	imp->name = ft_strdup("Imp");
	imp->rotatable = ROTATABLE;
	imp->anmtn_360[E_IDLE] = util_create_sprite_360_by_name(eng,
			"imp_idle");
	imp->anmtn_360[E_HURT] = util_create_sprite_360_by_name(eng,
			"imp_hurt");
	imp->anmtn_360[E_FIRE] = util_create_sprite_360_by_name(eng,
			"imp_fire");
	imp->anmtn_360[E_DEAD] = util_create_sprite_0_by_name(eng,
			"imp_dead");
	imp->shot = util_create_sprite_by_name(eng, "imp_shot");
	imp->anmtn_360[E_RUN] = imp->anmtn_360[E_IDLE];
	imp->anmtn[E_IDLE] = imp->anmtn_360[E_IDLE][EA_000];
	imp->anmtn[E_HURT] = imp->anmtn_360[E_HURT][EA_000];
	imp->anmtn[E_FIRE] = imp->anmtn_360[E_FIRE][EA_000];
	imp->anmtn[E_DEAD] = imp->anmtn_360[E_DEAD][EA_000];
	imp->anmtn[E_RUN] = imp->anmtn_360[E_RUN][EA_000];
	eng->enemy[IMP] = imp;
}
