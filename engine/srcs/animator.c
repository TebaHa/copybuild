/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:00:51 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/25 22:09:02 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		render_sprite_object(t_engine *eng, t_player plr, t_sprobject *spr_obj)
{
	t_point_2d	t1;
	t_point_2d	t2;
	t_point_2d	c1;
	t_point_2d	c2;

	t1.x = spr_obj->position.x + spr_obj->idle.surface->w / 2;
	t1.y = spr_obj->position.x + spr_obj->idle.surface->h / 2;
	t2.x = spr_obj->position.x - spr_obj->idle.surface->w / 2;
	t2.y = spr_obj->position.x - spr_obj->idle.surface->h / 2;

}