/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:14:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/13 15:21:55 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	shoot_help1(t_shoot_data *d, t_engine *eng,
		t_player *plr, int weapon_range)
{
	d->i = 0;
	d->res = 0;
	d->hit = 0;
	d->shoot.a = plr->position;
	d->angle_xy = atan2f(plr->sinangle, plr->cosangle);
	d->angle_z = -atanf(plr->yaw);
	d->dx = weapon_range * cosf(d->angle_xy) + d->shoot.a.x;
	d->dy = weapon_range * sinf(d->angle_xy) + d->shoot.a.y;
	d->dz = weapon_range * tanf(d->angle_z) + d->shoot.a.z;
	d->shoot.b = (t_point_3d){0, d->dx, d->dy, d->dz};
	d->prev = -1;
	engine_clear_checkstack(eng->world->checkqueue);
	engine_push_checkstack(eng->world->checkqueue, plr->cursector);
}

void	shoot_help2(t_shoot_data *d)
{
	d->plane.n = calc_normal_dots((t_point_3d){0,
	d->sect->objects_array[d->i].polies_array[0].
	vertices_array[0].x,
	d->sect->objects_array[d->i].polies_array[0].
	vertices_array[0].y, d->sect->floor},
	(t_point_3d){0, d->sect->objects_array[d->i].
	polies_array[0].vertices_array[0].x,
	d->sect->objects_array[d->i].polies_array[0].
	vertices_array[0].y, d->sect->ceil},
	(t_point_3d){0, d->sect->objects_array[d->i].
	polies_array[0].vertices_array[1].x,
	d->sect->objects_array[d->i].polies_array[0].
	vertices_array[1].y, d->sect->ceil});
	d->plane.p = (t_point_3d){0, d->sect->objects_array[d->i].
	polies_array[0].vertices_array[1].x,
	d->sect->objects_array[d->i].polies_array[0].
	vertices_array[1].y, d->sect->floor};
	d->res = intersect_3d_seg_plane(d->shoot, d->plane, &d->int_p);
}

int		shoot_help3(t_shoot_data *d, t_engine *eng, t_player *plr)
{
	if ((d->int_p.z < eng->world->sectors_array
	[d->sect->objects_array[d->i].portal].floor && d->int_p.z > d->sect->floor)
	|| (d->int_p.z > eng->world->sectors_array
	[d->sect->objects_array[d->i].portal]
	.ceil && d->int_p.z < d->sect->ceil))
	{
		engine_push_particlestack(&d->sect->objects_array[d->i], plr->wpn,
		(void *[2]){d->sect->objects_array[d->i].particles,
		&d->sect->objects_array[d->i].status}, d->int_p);
		return (1);
	}
	else if (d->prev != d->sect->objects_array[d->i].portal)
	{
		d->prev = d->sect_id;
		engine_push_checkstack(eng->world->checkqueue,
		d->sect->objects_array[d->i].portal);
		return (1);
	}
	return (0);
}

int		shoot_help4(t_shoot_data *d, t_engine *eng, t_player *plr)
{
	if (d->sect->objects_array[d->i].portal >= 0)
	{
		if (shoot_help3(d, eng, plr))
			return (1);
	}
	else if (d->prev != d->sect_id)
	{
		d->hit = 1;
		engine_push_particlestack(&d->sect->objects_array[d->i],
		plr->wpn, (void *[2]){d->sect->objects_array[d->i].particles,
		&d->sect->objects_array[d->i].status}, d->int_p);
		return (1);
	}
	return (0);
}

void	shoot(t_engine *eng, t_player *plr, int weapon_range)
{
	t_shoot_data	d;

	if (eng->aim)
	{
		kill(eng->aim);
		return ;
	}
	shoot_help1(&d, eng, plr, weapon_range);
	while (((d.sect_id = engine_pop_checkstack(eng->world->checkqueue)) >= 0))
	{
		d.i = 0;
		d.sect = &eng->world->sectors_array[d.sect_id];
		while (d.i < d.sect->objects_count)
		{
			shoot_help2(&d);
			if (d.res > 0 && check_point_inside_box(d.int_p,
			&d.sect->objects_array[d.i], d.sect->ceil, d.sect->floor))
			{
				if (shoot_help4(&d, eng, plr))
					break ;
			}
			d.i++;
		}
	}
}

void	kill(t_sprobject *sobj)
{
	int	i;

	i = 0;
	sobj->state = E_DEAD;
	sobj->type->anmtn[E_DEAD]->a_state = ANIMATE;
	while (i < 8)
	{
		sobj->type->anmtn_360[E_DEAD][i]->a_state = ANIMATE;
		i++;
	}
	sobj->frame_num = 0;
}
