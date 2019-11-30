/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:22:02 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/27 20:11:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_costil	relative_map_coordinate_to_absolute(t_player *plr,
			float map_y, float screen_x, float screen_y)
{
	float z;
	float x;

	z = (map_y * HEIGHT * VFOV) / ((HEIGHT / 2 - screen_y)
	- (plr->yaw * HEIGHT * VFOV));
	x = z * (WIDTH / 2 - screen_x) / (WIDTH * HFOV);
	return (ceiling_floor_screen_coordinates_to_map_coordinates(plr,
	z, x));
}

t_costil	ceiling_floor_screen_coordinates_to_map_coordinates(t_player *plr,
			float tz, float tx)
{
	t_costil	res;
	float		rtx;
	float		rtz;

	rtx = (tz) * plr->cosangle + (tx) * plr->sinangle;
	rtz = (tz) * plr->sinangle - (tx) * plr->cosangle;
	res.x = rtx + plr->position.x;
	res.z = rtz + plr->position.y;
	return (res);
}
