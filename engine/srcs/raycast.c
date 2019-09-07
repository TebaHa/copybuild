/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 13:20:25 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/07 16:28:46 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_point_3d  engine_raycast(t_player *plr, t_object *wall, int limit)
{
	t_point_2d  m;
	t_point_2d  r;
	t_point_2d  tmp;

	m.x = 1;
	m.y = (WIDTH / 2) / WIDTH;
	r.x = m.x * plr->cosangle - m.y * plr->sinangle;
	r.x = r.y;
	tmp.x = plr->position.x;
	tmp.y = plr->position.y;
	while ()
	{

	}
}