/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_items_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:29:13 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/10 01:05:10 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		eng_create_key_red(t_engine *eng)
{
	t_enemy	*key;

	if ((key = (t_enemy *)ft_memalloc(sizeof(t_enemy))) == NULL)
		util_malloc_error("key red");
	key->id = KEY_RED;
	key->name = ft_strdup("Red key");
	key->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "key_red");
	key->anmtn[E_RUN] = key->anmtn[E_IDLE];
	key->anmtn[E_FIRE] = key->anmtn[E_IDLE];
	key->anmtn[E_HURT] = key->anmtn[E_IDLE];
	key->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "empty_place");
	eng->enemy[KEY_RED] = key;
}

void		eng_create_key_blue(t_engine *eng)
{
	t_enemy	*key;

	if ((key = (t_enemy *)ft_memalloc(sizeof(t_enemy))) == NULL)
		util_malloc_error("key blue");
	key->id = KEY_BLUE;
	key->name = ft_strdup("Blue key");
	key->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "key_blue");
	key->anmtn[E_RUN] = key->anmtn[E_IDLE];
	key->anmtn[E_FIRE] = key->anmtn[E_IDLE];
	key->anmtn[E_HURT] = key->anmtn[E_IDLE];
	key->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "empty_place");
	eng->enemy[KEY_BLUE] = key;
}

void		eng_create_key_yellow(t_engine *eng)
{
	t_enemy	*key;

	if ((key = (t_enemy *)ft_memalloc(sizeof(t_enemy))) == NULL)
		util_malloc_error("key yellow");
	key->id = KEY_YELLOW;
	key->name = ft_strdup("Yellow key");
	key->anmtn[E_IDLE] = util_create_sprite_by_name(eng, "key_yellow");
	key->anmtn[E_RUN] = key->anmtn[E_IDLE];
	key->anmtn[E_FIRE] = key->anmtn[E_IDLE];
	key->anmtn[E_HURT] = key->anmtn[E_IDLE];
	key->anmtn[E_DEAD] = util_create_sprite_by_name(eng, "empty_place");
	eng->enemy[KEY_YELLOW] = key;
}
