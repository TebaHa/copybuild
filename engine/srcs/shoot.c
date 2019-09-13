/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:59:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/13 08:46:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

float	dot_product(t_point_3d a, t_point_3d b)
{
	float	res;

	res = 0;
	res += a.x * b.x;
	res += a.y * b.y;
	res += a.z * b.z;
	return (res);
}

void	shoot(t_engine *eng, t_player *plr, int weapon_range)
{
	t_point_3d	p_int;
	t_line		shoot;
	t_sector	*sect;
	t_item		sect_id;
	int			prev;
	int			i;

	i = 0;
	shoot.a = plr->position;
	double angle_xy = atan2f(plr->sinangle, plr->cosangle);
	double angle_z = atanf(plr->yaw);
	double dx = weapon_range * cosf(angle_xy) + shoot.a.x;
	double dy = weapon_range * sinf(angle_xy) + shoot.a.y;
	double dz = weapon_range * angle_z + shoot.a.z;
	shoot.b = (t_point_3d){0, shoot.a.x + dx, shoot.a.y + dy, shoot.a.z + dz};
	sect = &eng->world->sectors_array[plr->cursector];
	sect_id.sectorno = plr->cursector;
	engine_push_renderstack(eng->world->renderqueue, sect_id);
	while (((sect_id = engine_pop_renderstack(eng->world->renderqueue)).sectorno >= 0))
	{
		i = 0;
		while (i < eng->world->sectors_array[sect_id.sectorno].objects_count)
		{
			intersect_3d_seg_plane(sect);
			i++;
		}
		prev = sect_id.sectorno;
	}
	engine_clear_renderstack(eng->world->renderqueue);
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
	if (fabs(d) < 1e-10) // segment is parallel to plane
	{
		if (n == 0) // segment lies in plane
			return 2;
		else
			return 0; // no intersection
	}
	si = n / d; // they are not parallel compute intersect param
	if (si < 0 || si > 1)
		return 0; // no intersection
	*res = (t_point_3d){0, s.a.x + si * u.x, s.a.y + si * u.y, s.a.z + si * u.z}; // compute segment intersect point
	return 1;
}

void	engine_push_particlestack(t_point_3d *particlestack, int *status, t_point_3d point)
{
	particlestack[*status] = point;
	if ((*status) >= 9)
		*status = 0;
	else
		*status = *status + 1;
}