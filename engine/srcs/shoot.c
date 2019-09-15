/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:59:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/15 19:10:26 by fsmith           ###   ########.fr       */
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

void	shoot(t_engine *eng, SDL_Surface *surf, t_player *plr, int weapon_range)
{
	t_point_3d	int_p;
	t_line		shoot;
	t_plane		plane;
	t_sector	*sect;
	int			sect_id;
	int			prev;
	int			i;
	int			res;
	int			hit;

	i = 0;
	res = 0;
	hit = 0;
	shoot.a = plr->position;
	double angle_xy = atan2f(plr->sinangle, plr->cosangle);
	double angle_z = -atanf(plr->yaw);
	double dx = weapon_range * cosf(angle_xy) + shoot.a.x;
	double dy = weapon_range * sinf(angle_xy) + shoot.a.y;
	double dz = weapon_range * angle_z + shoot.a.z;
	shoot.b = (t_point_3d){0, shoot.a.x + dx, shoot.a.y + dy, shoot.a.z + dz};
	prev = -1;
	engine_clear_checkstack(eng->world->checkqueue);
	engine_push_checkstack(eng->world->checkqueue, plr->cursector);
	while (((sect_id = engine_pop_checkstack(eng->world->checkqueue)) >= 0))
	{
		i = 0;
		sect = &eng->world->sectors_array[sect_id];
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
			if (res > 0 && check_point_inside_box(int_p, &sect->objects_array[i], sect->ceil, sect->floor))
			{
				if (sect->objects_array[i].portal >= 0)
				{
					if (((int_p.z < eng->world->sectors_array[sect->objects_array[i].portal].floor && int_p.z > sect->floor)
					|| (int_p.z > eng->world->sectors_array[sect->objects_array[i].portal].ceil && int_p.z < sect->ceil)))
					{
						//printf("id: %d X: %f Y: %f Z: %f\n", sect->objects_array[i].id, int_p.x, int_p.y, int_p.z);
						hit = 1;
						engine_push_particlestack(sect->objects_array[i].particles, &sect->objects_array[i].status, int_p);
						break;
					}
					else if (prev != sect->objects_array[i].portal)
					{
						prev = sect_id;
						engine_push_checkstack(eng->world->checkqueue, sect->objects_array[i].portal);
						break;
					}
				}
				else if (prev != sect_id)
				{
					//printf("id: %d X: %f Y: %f Z: %f\n", sect->objects_array[i].id, int_p.x, int_p.y, int_p.z);
					hit = 1;
					engine_push_particlestack(sect->objects_array[i].particles, &sect->objects_array[i].status, int_p);
					break;
				}
			}
			i++;
		}
	}
	//printf("id: %d X: %f Y: %f Z: %f\n", sect->objects_array[i].id, sect->objects_array[i].particles[sect->objects_array[i].status - 1].x, sect->objects_array[i].particles[sect->objects_array[i].status - 1].y, sect->objects_array[i].particles[sect->objects_array[i].status - 1].z);
}

int		check_point_inside_box(t_point_3d a, t_object *obj, float ceil, float floor)
{
	t_point_3d	t0;
	t_point_3d	t1;

	if (obj->polies_array[0].vertices_array[0].x > obj->polies_array[0].vertices_array[1].x)
	{
		t0.x = obj->polies_array[0].vertices_array[0].x;
		t1.x = obj->polies_array[0].vertices_array[1].x;
	}
	else
	{
		t1.x = obj->polies_array[0].vertices_array[0].x;
		t0.x = obj->polies_array[0].vertices_array[1].x;
	}
	if (obj->polies_array[0].vertices_array[0].y > obj->polies_array[0].vertices_array[1].y)
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
	if (a.x <= t0.x && a.x >= t1.x && a.y <= t0.y && a.y >= t1.y && a.z <= t0.z && a.z >= t1.z)
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
	/*
	dir = (t_point_3d){0, s.b.x - s.a.x, s.b.y - s.a.y, s.b.z - s.a.z};
	d = dot_product(pn.n, pn.p);
	k = (d - dot_product(pn.n, s.a)) / dot_product(pn.n, dir);
	*res = (t_point_3d){0, s.a.x + dir.x * k, s.a.y + dir.y * k, s.a.z + dir.z * k};
	*/
	return (1);
}

void	engine_push_particlestack(t_point_3d *particlestack, int *status, t_point_3d point)
{
	particlestack[*status] = point;
	particlestack[*status].id = 1;
	if ((*status) >= 9)
		*status = 0;
	else
		*status = *status + 1;
}
