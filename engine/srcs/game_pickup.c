/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:49:25 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/27 20:11:01 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		check_sprites_in_sector(t_player *plr, t_sector *sect)
{
	int		i;

	i = 0;
	while (i < sect->sprobjects_count)
	{
		if (sect->sprobjects_array[i].norender == false)
			check_sprite_pick(plr, &sect->sprobjects_array[i]);
		i++;
	}
}

void		check_sprite_pick(t_player *plr, t_sprobject *sobj)
{
	double	dist;
	double	tmp;

	if (sobj->enum_type == MEDKIT || sobj->enum_type == ARMOR
	|| sobj->enum_type == PLASMA_AMMO || sobj->enum_type == RIFLE_AMMO
	|| sobj->enum_type == POWER_UP)
	{
		tmp = pow((plr->position.x - sobj->position.x), 2)
		+ pow((plr->position.y - sobj->position.y), 2);
		if (tmp <= 0.1)
			return ;
		dist = sqrt(tmp);
		if (dist <= 20.1)
			apply_sprite_obj(plr, sobj);
	}
}

void		apply_sprite_obj(t_player *plr, t_sprobject *sobj)
{
	t_bool		picked;

	picked = false;
	if (sobj->enum_type == MEDKIT)
		picked = modify_players_stat(&plr->health, 25, 100);
	else if (sobj->enum_type == ARMOR)
		picked = modify_players_stat(&plr->armor, 25, 100);
	else if (sobj->enum_type == POWER_UP)
		picked = modify_players_stat(&plr->health, 200, 200);
	else if (sobj->enum_type == PLASMA_AMMO)
	{
		if (ft_strcmp(plr->wpn->name, "Plazma gun") == 0)
			picked = modify_players_stat(&plr->wpn->ammo, 10, 50);
	}
	else if (sobj->enum_type == RIFLE_AMMO)
	{
		if (ft_strcmp(plr->wpn->name, "Rifle") == 0)
			picked = modify_players_stat(&plr->wpn->ammo, 25, 300);
	}
	if (picked == true)
		sobj->norender = true;
}

t_bool		modify_players_stat(int *stat, int addtion, int limit)
{
	int		result;

	if (*stat >= limit)
		return (false);
	result = *stat + addtion;
	if (result > limit)
		result = limit;
	*stat = result;
	return (true);
}
