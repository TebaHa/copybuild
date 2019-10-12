/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:37:20 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/29 17:06:43 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		eng_create_hud(t_engine *eng)
{
	eng->hud = (t_hud *)ft_memalloc(sizeof(t_hud));
	eng->hud->emo_state = F_IDLE;
	eng->hud->health_state = H_100;
//	eng->hud->health = util_create_sprite_by_name(eng, "hud_health");
//	eng->hud->armor = util_create_sprite_by_name(eng, "hud_armor");
//	eng->hud->ammo = util_create_sprite_by_name(eng, "hud_ammo");
	eng_create_face(eng);
}
