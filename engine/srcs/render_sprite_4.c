/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 14:56:26 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 14:56:35 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	get_sprite_rotatable_obj(t_player *plr,
		t_sprobject *obj, t_sprt_r *d)
{
	t_point_2d	obj_dir;
	t_point_2d	plr_dir;
	float		angle;
	float		dot;
	float		det;

	obj_dir = (t_point_2d){plr->position.x - obj->position.x,
	plr->position.y - obj->position.y};
	plr_dir = (t_point_2d){-obj->position.x, -obj->position.y};
	dot = obj_dir.x * plr_dir.x + obj_dir.y * plr_dir.y;
	det = obj_dir.x * plr_dir.y - obj_dir.y * plr_dir.x;
	angle = atan2(det, dot);
	angle = ((int)((angle * 180.0 / M_PI) + 180) + obj->angle) % 360;
	get_sprite_anim_obj(get_id_by_angle(angle), plr, obj, d);
}
