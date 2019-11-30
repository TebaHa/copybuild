/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_pickup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:49:25 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/30 18:36:33 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		check_sprites_in_sector(t_player *plr, t_sector *sect)
{
	int		i;

	i = 0;
	while (i < sect->sprobjects_count)
	{
		if (sect->sprobjects_array[i].norender == false)
		{
			sect->sprobjects_array[i].position.z = sect->floor;
			check_sprite_pick(plr, &sect->sprobjects_array[i]);
		}
		i++;
	}
}

void		check_sprite_pick(t_player *plr, t_sprobject *sobj)
{
	double	dist;
	double	tmp;

	if (sobj->enum_type == MEDKIT || sobj->enum_type == ARMOR
	|| sobj->enum_type == PLASMA_AMMO || sobj->enum_type == RIFLE_AMMO
	|| sobj->enum_type == POWER_UP || sobj->enum_type == KEY_RED ||
	sobj->enum_type == KEY_BLUE || sobj->enum_type == KEY_YELLOW ||
	sobj->enum_type == JETPACK)
	{
		tmp = pow((plr->position.x - sobj->position.x), 2)
		+ pow((plr->position.y - sobj->position.y), 2)
		+ pow((plr->position.z - 150 - sobj->position.z), 2);
		if (tmp <= 0.1)
			return ;
		dist = sqrt(tmp);
		if (dist <= 30.1)
			apply_sprite_obj(plr, sobj);
	}
}

t_bool		apply_sprite_key(t_player *plr, t_sprobject *sobj)
{
	t_bool	res;

	res = false;
	if (sobj->enum_type == KEY_RED)
	{
		res = true;
		plr->key_red = true;
	}
	else if (sobj->enum_type == KEY_BLUE)
	{
		res = true;
		plr->key_blue = true;
	}
	else if (sobj->enum_type == KEY_YELLOW)
	{
		res = true;
		plr->key_yellow = true;
	}
	return (res);
}

void		apply_sprite_obj(t_player *plr, t_sprobject *sobj)
{
	t_bool		picked;

	picked = false;
	if (sobj->enum_type == MEDKIT)
		picked = modify_players_stat(&plr->health, 25, 100);
	else if (sobj->enum_type == JETPACK)
	{
		plr->grav = false;
		picked = true;
	}
	else if (sobj->enum_type == ARMOR)
		picked = modify_players_stat(&plr->armor, 25, 100);
	else if (sobj->enum_type == POWER_UP)
	{
		engine_replace_text(plr, "HP INCREASED TO MAX LEVEL");
		picked = modify_players_stat(&plr->health, 200, 200);
	}
	else if (sobj->enum_type == PLASMA_AMMO
	|| sobj->enum_type == RIFLE_AMMO)
		picked = apply_sprite_obj_help(plr, sobj);
	else
		picked = apply_sprite_key(plr, sobj);
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
