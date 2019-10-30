/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:59:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/27 20:13:08 by zytrams          ###   ########.fr       */
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

int		check_point_inside_box(t_point_3d a,
		t_object *obj, float ceil, float floor)
{
	t_point_3d	t0;
	t_point_3d	t1;

	point_swapper_shoot(&t0.x, &t1.x, obj->vertices_array[0].x,
	obj->vertices_array[1].x);
	point_swapper_shoot(&t0.y, &t1.y, obj->vertices_array[0].y,
	obj->vertices_array[1].y);
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
			return (2);
		else
			return (0);
	}
	si = n / d;
	if (si < 0 || si > 1)
		return (0);
	*res = (t_point_3d){0, s.a.x + si * u.x,
	s.a.y + si * u.y, s.a.z + si * u.z};
	return (1);
}

void	engine_push_partclstack_help(t_sh_part *data,
		t_object *obj, t_weapon *wpn, t_point_3d *particle)
{
	data->dx1 = obj->vertices_array[0].x - particle->x;
	data->dy1 = obj->vertices_array[0].y - particle->y;
	data->dx2 = particle->x - obj->vertices_array[1].x;
	data->dy2 = particle->y - obj->vertices_array[1].y;
	data->dist1 = sqrtf(data->dx1 * data->dx1 + data->dy1 * data->dy1);
	data->dist2 = sqrtf(data->dx2 * data->dx2 + data->dy2 * data->dy2);
	data->half_w = wpn->bullet_hole->surface[0]->w / 16;
	data->w_partcle.texture = wpn->bullet_hole;
}

void	engine_push_particlestack(t_object *obj, t_weapon *wpn,
		void *d[2], t_point_3d particle)
{
	t_sh_part	data;
	t_wallobj	*particlestack;
	int			*status;

	particlestack = (t_wallobj *)d[0];
	status = (int *)d[1];
	engine_push_partclstack_help(&data, obj, wpn, &particle);
	data.w_partcle.a.x = particle.x - ((data.half_w * (particle.x
	- obj->vertices_array[0].x)) / data.dist1);
	data.w_partcle.a.y = particle.y - ((data.half_w * (particle.y
	- obj->vertices_array[0].y)) / data.dist1);
	data.w_partcle.b.x = particle.x - ((data.half_w * (particle.x
	- obj->vertices_array[1].x)) / data.dist2);
	data.w_partcle.b.y = particle.y - ((data.half_w * (particle.y
	- obj->vertices_array[1].y)) / data.dist2);
	data.w_partcle.id = 1;
	data.w_partcle.z = particle.z;
	data.w_partcle.timer = 0;
	data.w_partcle.frame_num = 0;
	particlestack[*status] = data.w_partcle;
	*status = (*status > 126) ? 0 : *status + 1;
}
