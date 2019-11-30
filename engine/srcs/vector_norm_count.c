/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 15:38:11 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/27 20:14:04 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_point_3d		cross_vec3(t_point_3d v1, t_point_3d v2)
{
	t_point_3d	v3normal;

	v3normal.x = (v1.y * v2.z) - (v1.z * v2.y);
	v3normal.y = (v1.z * v2.x) - (v1.x * v2.z);
	v3normal.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (v3normal);
}

t_point_3d		create_vector(t_point_3d *a, t_point_3d *b)
{
	t_point_3d vec3;

	vec3.x = a->x - b->x;
	vec3.y = a->y - b->y;
	vec3.z = a->z - b->z;
	return (vec3);
}

double			magnitude(t_point_3d *normal)
{
	return (sqrt((normal->x * normal->x) +
	(normal->y * normal->y) + (normal->z * normal->z)));
}

void			normalize_vec3(t_point_3d *normal)
{
	double	magn;

	magn = magnitude(normal);
	normal->x /= magn;
	normal->y /= magn;
	normal->z /= magn;
}

t_point_3d		calc_normal_dots(t_point_3d a, t_point_3d b, t_point_3d c)
{
	t_point_3d		vec1;
	t_point_3d		vec2;
	t_point_3d		normal;

	vec1 = create_vector(&(a), &(b));
	vec2 = create_vector(&(b), &(c));
	normal = cross_vec3(vec1, vec2);
	normalize_vec3(&normal);
	return (normal);
}
