/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hud_face.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:20:03 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/29 17:19:20 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		eng_create_face(t_engine *eng)
{
	eng_create_face_100_0(eng);
}

void		eng_create_face_100_0(t_engine *eng)
{
	eng->hud->face[H_100][F_IDLE] = util_create_sprite_by_name(eng, "face_100_idle");
	eng->hud->face[H_100][F_HAPPY] = util_create_sprite_by_name(eng, "face_100_happy");
	eng->hud->face[H_100][F_LEFT] = util_create_sprite_by_name(eng, "face_100_left");
	eng->hud->face[H_100][F_RIGHT] = util_create_sprite_by_name(eng, "face_100_right");
	eng->hud->face[H_100][F_SHOOT] = util_create_sprite_by_name(eng, "face_100_shoot");
	eng->hud->face[H_100][F_HURT] = util_create_sprite_by_name(eng, "face_100_hurt");

	eng->hud->face[H_80][F_IDLE] = util_create_sprite_by_name(eng, "face_80_idle");
	eng->hud->face[H_80][F_HAPPY] = util_create_sprite_by_name(eng, "face_80_happy");
	eng->hud->face[H_80][F_LEFT] = util_create_sprite_by_name(eng, "face_80_left");
	eng->hud->face[H_80][F_RIGHT] = util_create_sprite_by_name(eng, "face_80_right");
	eng->hud->face[H_80][F_SHOOT] = util_create_sprite_by_name(eng, "face_80_shoot");
	eng->hud->face[H_80][F_HURT] = util_create_sprite_by_name(eng, "face_80_hurt");

	eng->hud->face[H_60][F_IDLE] = util_create_sprite_by_name(eng, "face_60_idle");
	eng->hud->face[H_60][F_HAPPY] = util_create_sprite_by_name(eng, "face_60_happy");
	eng->hud->face[H_60][F_LEFT] = util_create_sprite_by_name(eng, "face_60_left");
	eng->hud->face[H_60][F_RIGHT] = util_create_sprite_by_name(eng, "face_60_right");
	eng->hud->face[H_60][F_SHOOT] = util_create_sprite_by_name(eng, "face_60_shoot");
	eng->hud->face[H_60][F_HURT] = util_create_sprite_by_name(eng, "face_60_hurt");

	eng->hud->face[H_40][F_IDLE] = util_create_sprite_by_name(eng, "face_40_idle");
	eng->hud->face[H_80][F_HAPPY] = util_create_sprite_by_name(eng, "face_40_happy");
	eng->hud->face[H_40][F_LEFT] = util_create_sprite_by_name(eng, "face_40_left");
	eng->hud->face[H_40][F_RIGHT] = util_create_sprite_by_name(eng, "face_40_right");
	eng->hud->face[H_80][F_SHOOT] = util_create_sprite_by_name(eng, "face_40_shoot");
	eng->hud->face[H_80][F_HURT] = util_create_sprite_by_name(eng, "face_40_hurt");

	eng->hud->face[H_20][F_IDLE] = util_create_sprite_by_name(eng, "face_20_idle");
	eng->hud->face[H_80][F_HAPPY] = util_create_sprite_by_name(eng, "face_20_happy");
	eng->hud->face[H_20][F_LEFT] = util_create_sprite_by_name(eng, "face_20_left");
	eng->hud->face[H_20][F_RIGHT] = util_create_sprite_by_name(eng, "face_20_right");
	eng->hud->face[H_80][F_SHOOT] = util_create_sprite_by_name(eng, "face_20_shoot");
	eng->hud->face[H_80][F_HURT] = util_create_sprite_by_name(eng, "face_20_hurt");

	eng->hud->face[H_0][F_IDLE] = util_create_sprite_by_name(eng, "face_dead");
	eng->hud->face[H_0][F_HAPPY] = eng->hud->face[H_0][F_IDLE];
	eng->hud->face[H_0][F_LEFT] = eng->hud->face[H_0][F_IDLE];
	eng->hud->face[H_0][F_RIGHT] = eng->hud->face[H_0][F_IDLE];
	eng->hud->face[H_0][F_SHOOT] = eng->hud->face[H_0][F_IDLE];
	eng->hud->face[H_0][F_HURT] = eng->hud->face[H_0][F_IDLE];
}
