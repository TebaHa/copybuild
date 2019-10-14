/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_funs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:57:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/14 20:56:24 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

/*
** IntersectBox: Determine whether two 2D-boxes intersect.
*/
short		intersect_box(t_point_2d x0, t_point_2d x1, t_point_2d x2, t_point_2d x3)
{
	return (overlap(x0.x, x1.x, x2.x, x3.x)
	&& overlap(x0.y, x1.y, x2.y, x3.y));
}

/*
** PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
*/
float		point_side(t_point_2d p, t_point_2d x0, t_point_2d x1)
{
	return (vxs((x1.x) - (x0.x), (x1.y) - (x0.y),
	(p.x) - (x0.x), (p.y) - (x0.y)));
}

/*
** Intersect: Calculate the point of intersection between two lines.
*/
t_point_2d	intersect(t_point_2d x1, t_point_2d x2, t_point_2d x3, t_point_2d x4)
{
	return ((t_point_2d) {
	vxs(vxs(x1.x, x1.y, x2.x, x2.y),
	(x1.x - x2.x), vxs(x3.x, x3.y, x4.x, x4.y), (x3.x - x4.x))
	/ vxs((x1.x - x2.x), (x1.y - x2.y), (x3.x - x4.x), (x3.y - x4.y)),
	vxs(vxs(x1.x, x1.y, x2.x, x2.y), (x1.y - x2.y), vxs(x3.x, x3.y, x4.x, x4.y),
	(x3.y - x4.y)) / vxs((x1.x) - (x2.x), (x1.y) - (x2.y),
	(x3.x - x4.x), (x3.y - x4.y))});
}

/*
** Scaler for textures
*/
t_scaler	scaler_init(float data[5])
{
	return (t_scaler){data[3] + (data[1] - 1 - data[0])
	* (data[4] - data[3]) / (data[2] - data[0]),
	((data[4] < data[3]) ^ (data[2] < data[0])) ? -1 : 1,
	fabsf(data[4] - data[3]), fabsf(data[2] - data[0]), (int)((data[1] - 1 - data[0])
	* fabsf(data[4] - data[3])) % (int)fabsf(data[2] - data[0])};
}
