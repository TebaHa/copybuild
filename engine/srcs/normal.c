/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 15:38:11 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/14 11:56:19 by fsmith           ###   ########.fr       */
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
	t_point_3d		t[3];

	vec1 = create_vector(&(a), &(b));
	vec2 = create_vector(&(b), &(c));
	normal = cross_vec3(vec1, vec2);
	normalize_vec3(&normal);
	if (normal.y < 0)
		normal.y = -normal.y;
	if (normal.x < 0)
		normal.x = -normal.x;
	if (normal.z < 0)
		normal.z = -normal.z;
	return (normal);
}

t_point_3d		calc_normal(t_polygone *poly)
{
	t_point_3d		vec1;
	t_point_3d		vec2;
	t_point_3d		normal;
	t_point_3d		t[3];

	t[0] = (t_point_3d){poly->vertices_array[0].x, poly->vertices_array[0].y, poly->vertices_array[0].z};
	t[1] = (t_point_3d){poly->vertices_array[1].x, poly->vertices_array[1].y, poly->vertices_array[1].z};
	t[2] = (t_point_3d){poly->vertices_array[2].x, poly->vertices_array[2].y, poly->vertices_array[2].z};
	vec1 = create_vector(&(t[2]), &(t[1]));
	vec2 = create_vector(&(t[1]), &(t[0]));
	normal = cross_vec3(vec1, vec2);
	normalize_vec3(&normal);
	if (normal.y < 0)
		normal.y = -normal.y;
	if (normal.x < 0)
		normal.x = -normal.x;
	if (normal.z < 0)
		normal.z = -normal.z;
	return (normal);
}
