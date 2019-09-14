/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:59:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/14 11:56:19 by fsmith           ###   ########.fr       */
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
	t_point_3d	int_p;
	t_line		shoot;
	t_plane		plane;
	t_sector	*sect;
	int			sect_id;
	int			prev;
	int			i;
	int			res;

	i = 0;
	res = 0;
	shoot.a = plr->position;
	double angle_xy = atan2f(plr->sinangle, plr->cosangle);
	double angle_z = atanf(plr->yaw);
	double dx = weapon_range * cosf(angle_xy) + shoot.a.x;
	double dy = weapon_range * sinf(angle_xy) + shoot.a.y;
	double dz = weapon_range * angle_z + shoot.a.z;
	shoot.b = (t_point_3d){0, shoot.a.x + dx, shoot.a.y + dy, shoot.a.z + dz};
	prev = plr->cursector;
	engine_clear_checkstack(eng->world->checkqueue);
	engine_push_checkstack(eng->world->checkqueue, plr->cursector);
	while (((sect_id = engine_pop_checkstack(eng->world->checkqueue)) >= 0))
	{
		i = 0;
		sect = &eng->world->sectors_array[sect_id];
		printf("sect %d prev %d\n", sect_id, prev);
		while (i < sect->objects_count)
		{
			plane.n = calc_normal_dots((t_point_3d){0, sect->objects_array[i].polies_array[0].vertices_array[0].x,
			sect->objects_array[i].polies_array[0].vertices_array[0].y, sect->floor},
			(t_point_3d){0, sect->objects_array[i].polies_array[0].vertices_array[1].x,
			sect->objects_array[i].polies_array[0].vertices_array[1].y, sect->floor},
			(t_point_3d){0, sect->objects_array[i].polies_array[0].vertices_array[1].x,
			sect->objects_array[i].polies_array[0].vertices_array[1].y, sect->ceil});
			plane.p = (t_point_3d){0, sect->objects_array[i].polies_array[0].vertices_array[1].x,
			sect->objects_array[i].polies_array[0].vertices_array[1].y, sect->floor};
			res = intersect_3d_seg_plane(shoot, plane, &int_p);
			if (res > 0)
			{
				if (sect->objects_array[i].portal != -1 && prev != sect->objects_array[i].portal)
					engine_push_checkstack(eng->world->checkqueue, sect->objects_array[i].portal);
				else
					engine_push_particlestack(sect->objects_array[i].particles, &sect->objects_array[i].status, int_p);
				break;
			}
			i++;
		}
		prev = sect_id;
	}
	printf("X: %f Y: %f Z: %f\n", int_p.x, int_p.y, int_p.z);
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
