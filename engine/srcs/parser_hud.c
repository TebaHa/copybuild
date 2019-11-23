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
	eng->hud->health = util_create_sprite_by_name(eng, "hud_health");
	eng->hud->armor = util_create_sprite_by_name(eng, "hud_armor");
	eng->hud->ammo = util_create_sprite_by_name(eng, "hud_ammo");
	eng->hud->key_red = util_create_sprite_by_name(eng, "key_red_1");
	eng->hud->key_blue = util_create_sprite_by_name(eng, "key_blue_1");
	eng->hud->key_yellow = util_create_sprite_by_name(eng, "key_yellow_1");
	eng_create_face_100_60(eng, eng->hud);
	eng_create_face_40_0(eng, eng->hud);
}

void		eng_create_face_100_60(t_engine *eng, t_hud *h)
{
	h->face[H_100][F_IDLE] = util_create_sprite_by_name(eng, "face_100_idle");
	h->face[H_100][F_HAPPY] = util_create_sprite_by_name(eng, "face_100_happy");
	h->face[H_100][F_LEFT] = util_create_sprite_by_name(eng, "face_100_left");
	h->face[H_100][F_RIGHT] = util_create_sprite_by_name(eng, "face_100_right");
	h->face[H_100][F_SHOOT] = util_create_sprite_by_name(eng, "face_100_shoot");
	h->face[H_100][F_HURT] = util_create_sprite_by_name(eng, "face_100_hurt");
	h->face[H_80][F_IDLE] = util_create_sprite_by_name(eng, "face_80_idle");
	h->face[H_80][F_HAPPY] = util_create_sprite_by_name(eng, "face_80_happy");
	h->face[H_80][F_LEFT] = util_create_sprite_by_name(eng, "face_80_left");
	h->face[H_80][F_RIGHT] = util_create_sprite_by_name(eng, "face_80_right");
	h->face[H_80][F_SHOOT] = util_create_sprite_by_name(eng, "face_80_shoot");
	h->face[H_80][F_HURT] = util_create_sprite_by_name(eng, "face_80_hurt");
	h->face[H_60][F_IDLE] = util_create_sprite_by_name(eng, "face_60_idle");
	h->face[H_60][F_HAPPY] = util_create_sprite_by_name(eng, "face_60_happy");
	h->face[H_60][F_LEFT] = util_create_sprite_by_name(eng, "face_60_left");
	h->face[H_60][F_RIGHT] = util_create_sprite_by_name(eng, "face_60_right");
	h->face[H_60][F_SHOOT] = util_create_sprite_by_name(eng, "face_60_shoot");
	h->face[H_60][F_HURT] = util_create_sprite_by_name(eng, "face_60_hurt");
}

void		eng_create_face_40_0(t_engine *eng, t_hud *h)
{
	h->face[H_40][F_IDLE] = util_create_sprite_by_name(eng, "face_40_idle");
	h->face[H_40][F_HAPPY] = util_create_sprite_by_name(eng, "face_40_happy");
	h->face[H_40][F_LEFT] = util_create_sprite_by_name(eng, "face_40_left");
	h->face[H_40][F_RIGHT] = util_create_sprite_by_name(eng, "face_40_right");
	h->face[H_40][F_SHOOT] = util_create_sprite_by_name(eng, "face_40_shoot");
	h->face[H_40][F_HURT] = util_create_sprite_by_name(eng, "face_40_hurt");
	h->face[H_20][F_IDLE] = util_create_sprite_by_name(eng, "face_20_idle");
	h->face[H_20][F_HAPPY] = util_create_sprite_by_name(eng, "face_20_happy");
	h->face[H_20][F_LEFT] = util_create_sprite_by_name(eng, "face_20_left");
	h->face[H_20][F_RIGHT] = util_create_sprite_by_name(eng, "face_20_right");
	h->face[H_20][F_SHOOT] = util_create_sprite_by_name(eng, "face_20_shoot");
	h->face[H_20][F_HURT] = util_create_sprite_by_name(eng, "face_20_hurt");
	h->face[H_0][F_IDLE] = util_create_sprite_by_name(eng, "face_dead");
	h->face[H_0][F_HAPPY] = h->face[H_0][F_IDLE];
	h->face[H_0][F_LEFT] = h->face[H_0][F_IDLE];
	h->face[H_0][F_RIGHT] = h->face[H_0][F_IDLE];
	h->face[H_0][F_SHOOT] = h->face[H_0][F_IDLE];
	h->face[H_0][F_HURT] = h->face[H_0][F_IDLE];
}
