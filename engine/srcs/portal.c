/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:42:18 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/06 20:40:13 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	create_portal_map(t_portals *lvl)
{
	lvl->wall_count = 12;
	lvl->sector_count = 3;
	lvl->sector_array = (t_sector *)ft_memalloc(sizeof(t_sector) * 3);
	lvl->wall_array = (t_wall *)ft_memalloc(sizeof(t_wall) * 12);
	create_sector(0, lvl->sector_array, 4, 0);
	create_sector(1, (lvl->sector_array + 1), 4, 4);
	create_sector(2, (lvl->sector_array + 2), 4, 8);
	create_wall(0, lvl->wall_array, (t_point){100L, 100L}, (t_point){100L, 150L}, -1);
	create_wall(1, lvl->wall_array + 1, (t_point){100L, 150L}, (t_point){150L, 150L}, -1);
	create_wall(2, lvl->wall_array + 2, (t_point){150L, 150L}, (t_point){150L, 100L}, 1);
	create_wall(3, lvl->wall_array + 3, (t_point){150L, 100L}, (t_point){100L, 100L}, -1);
	create_wall(4, lvl->wall_array + 4, (t_point){150L, 100L}, (t_point){150L, 150L}, 0);
	create_wall(5, lvl->wall_array + 5, (t_point){150L, 150L}, (t_point){200L, 200L}, -1);
	create_wall(6, lvl->wall_array + 6, (t_point){200L, 200L}, (t_point){200L, 150L}, 2);
	create_wall(7, lvl->wall_array + 7, (t_point){200L, 150L}, (t_point){150L, 100L}, -1);
	create_wall(8, lvl->wall_array + 8, (t_point){200L, 150L}, (t_point){200L, 200L}, 1);
	create_wall(9, lvl->wall_array + 9, (t_point){200L, 200L}, (t_point){250L, 200L}, -1);
	create_wall(10, lvl->wall_array + 10, (t_point){250L, 200L}, (t_point){250L, 150L}, -1);
	create_wall(11, lvl->wall_array + 11, (t_point){250L, 150L}, (t_point){200, 150L}, -1);
}

void	create_sector(long id, t_sector *sector, long size, long start)
{
	sector->id = id;
	sector->start_wall = start;
	sector->walls_count = size;
}

void	create_wall(long id, t_wall *array, t_point a, t_point b, long portal)
{
	array->id = id;
	array->pos.a = a;
	array->pos.b = b;
	array->next_sector = portal;
}
