/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:32:24 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 14:31:35 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int		check_point_inside_wbox(t_point_3d a,
		t_wallobj *obj, float ceil, float floor)
{
	t_point_3d	t0;
	t_point_3d	t1;

	point_swapper_shoot(&t0.x, &t1.x, obj->a.x,
	obj->b.x);
	point_swapper_shoot(&t0.y, &t1.y, obj->a.y,
	obj->b.y);
	t0.z = obj->z + obj->texture->surface[0]->h / 4;
	t1.z = obj->z - obj->texture->surface[0]->h / 4;
	if (a.x <= t0.x + 0.1 && a.x >= t1.x - 0.1
	&& a.y <= t0.y + 0.1 && a.y >= t1.y - 0.1
	&& a.z <= t0.z + 0.1 && a.z >= t1.z - 0.1)
		return (1);
	return (0);
}

void	use(t_engine *eng, t_player *plr)
{
	t_shoot_data	d;
	int				i;

	shoot_help1(&d, eng, plr, 100);
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
				i = 0;
				while (i < d.sect->objects_array[d.i].wallobjects_num)
				{
					if (check_point_inside_wbox(d.int_p,
					&d.sect->objects_array[d.i].stuff[i],
					d.sect->ceil, d.sect->floor))
					{
						add_task(eng,
						&eng->world->sectors_array[d.sect->objects_array[d.i].wallobjects_array[i].sector_id],
						&d.sect->objects_array[d.i].wallobjects_array[i], plr);
						break ;
					}
					i++;
				}
				break ;
			}
			d.i++;
		}
	}
}

void	add_task(t_engine *eng, t_sector *sect, t_wobj *obj, t_player *plr)
{
	t_bool	red;
	t_bool	blue;
	t_bool	yellow;

	red = true;
	blue = true;
	yellow = true;
	if (obj->enum_type == BT_DOOR)
	{
		if (obj->red_key)
			red = plr->key_red;
		if (obj->blue_key)
			blue = plr->key_blue;
		if (obj->yellow_key)
			yellow = plr->key_yellow;
		if (red && blue && yellow)
		{
			sect->opening.delta = 10;
			engine_push_doorqueue(eng->doors, &sect->opening);
		}
	}
	else if (obj->enum_type == BT_FINISH)
		eng->ending = true;
}
