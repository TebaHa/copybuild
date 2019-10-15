/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:59:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/15 21:18:44 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

float	dot_product(t_point_3d a, t_point_3d b)
{
	float	res;

	res = 0;
	res += a.x * b.x;
	res += a.y * b.y;
	res += a.z * b.z;
	return (res);
}

int		check_point_inside_box(t_point_3d a, t_object *obj, float ceil, float floor)
{
	t_point_3d	t0;
	t_point_3d	t1;

	if (obj->polies_array[0].vertices_array[0].x
	> obj->polies_array[0].vertices_array[1].x)
	{
		t0.x = obj->polies_array[0].vertices_array[0].x;
		t1.x = obj->polies_array[0].vertices_array[1].x;
	}
	else
	{
		t1.x = obj->polies_array[0].vertices_array[0].x;
		t0.x = obj->polies_array[0].vertices_array[1].x;
	}
	if (obj->polies_array[0].vertices_array[0].y
	> obj->polies_array[0].vertices_array[1].y)
	{
		t0.y = obj->polies_array[0].vertices_array[0].y;
		t1.y = obj->polies_array[0].vertices_array[1].y;
	}
	else
	{
		t1.y = obj->polies_array[0].vertices_array[0].y;
		t0.y = obj->polies_array[0].vertices_array[1].y;
	}
	t0.z = ceil;
	t1.z = floor;
	if (a.x <= t0.x + 0.1 && a.x >= t1.x - 0.1
	&& a.y <= t0.y + 0.1 && a.y >= t1.y - 0.1
	&& a.z <= t0.z + 0.1 && a.z >= t1.z - 0.1)
		return (1);
	return (0);
}

int		intersect_3d_seg_plane(t_line s, t_plane pn, t_point_3d *res)
{
	t_point_3d	u;
	t_point_3d	w;
	float		d;
	float		n;
	float		si;

	u = (t_point_3d){0, s.b.x - s.a.x, s.b.y - s.a.y, s.b.z - s.a.z};
	w = (t_point_3d){0, s.a.x - pn.p.x, s.a.y - pn.p.y, s.a.z - pn.p.z};
	d = dot_product(pn.n, u);
	n = -dot_product(pn.n, w);
	if (fabs(d) < 1e-10)
	{
		if (n == 0)
			return 2;
		else
			return 0;
	}
	si = n / d;
	if (si < 0 || si > 1)
		return 0;
	*res = (t_point_3d){0, s.a.x + si * u.x, s.a.y + si * u.y, s.a.z + si * u.z};
	return (1);
}

void	engine_push_particlestack(t_object *obj, t_weapon *wpn,
		t_wallobj *particlestack, int *status, t_point_3d particle)
{
	t_wallobj	w_partcle;
	double		dx1;
	double		dy1;
	double		dx2;
	double		dy2;
	double		dist1;
	double		dist2;
	double		half_w;

	dx1 = obj->polies_array[0].vertices_array[0].x - particle.x;
	dy1 = obj->polies_array[0].vertices_array[0].y - particle.y;
	dx2 = particle.x - obj->polies_array[0].vertices_array[1].x;
	dy2 = particle.y - obj->polies_array[0].vertices_array[1].y;
	dist1 = sqrtf(dx1 * dx1 + dy1 * dy1);
	dist2 = sqrtf(dx2 * dx2 + dy2 * dy2);
	half_w = wpn->bullet_hole->surface[0]->w / 16;
	w_partcle.texture = wpn->bullet_hole;
	w_partcle.a.x = particle.x - ((half_w * (particle.x
	- obj->polies_array[0].vertices_array[0].x)) / dist1);
	w_partcle.a.y = particle.y - ((half_w * (particle.y
	- obj->polies_array[0].vertices_array[0].y)) / dist1);
	w_partcle.b.x = particle.x - ((half_w * (particle.x
	- obj->polies_array[0].vertices_array[1].x)) / dist2);
	w_partcle.b.y = particle.y - ((half_w * (particle.y
	- obj->polies_array[0].vertices_array[1].y)) / dist2);
	w_partcle.id = 1;
	w_partcle.z = particle.z;
	w_partcle.timer = 0;
	w_partcle.frame_num = 0;
	particlestack[*status] = w_partcle;
	*status = (*status > 126) ? 0 : *status + 1;
}
