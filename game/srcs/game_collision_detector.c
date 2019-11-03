/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_collision_detector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 10:48:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/03 12:36:26 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int		line_intersection_check(t_line_2d a, t_line_2d b)
{
	float		det;
	t_point_2d	rs;
	t_point_2d	a_dir;
	t_point_2d	b_dir;
	t_point_2d	c_dir;

	a_dir = (t_point_2d){a.b.x - a.a.x,
	a.b.y - a.a.y};
	b_dir = (t_point_2d){b.a.x - b.b.x,
	b.a.y - b.b.y};
	c_dir = (t_point_2d){b.a.x - a.a.x,
	b.a.y - a.a.y};
	det = a_dir.x * b_dir.y - a_dir.y * b_dir.x;
	if (det == 0)
		return (0);
	rs.x = (c_dir.x * b_dir.y - c_dir.y * b_dir.x) / det;
	rs.y = (a_dir.x * c_dir.y - a_dir.y * c_dir.x) / det;
	return (!(rs.x < 0.f || rs.x > 1.0
	|| rs.y < 0.f || rs.y > 1.0));
}

int		check_wall_passed(t_line_2d plr_dir, int cursect, t_sector *sector)
{
	int	i;

	i = 0;
	while (i < sector->objects_count)
	{
		if (line_intersection_check(plr_dir,
		(t_line_2d){(t_point_2d)
		{sector->objects_array[i].polies_array[0].vertices_array[0].x,
		sector->objects_array[i].polies_array[0].vertices_array[0].y},
		(t_point_2d)
		{sector->objects_array[i].polies_array[0].vertices_array[1].x,
		sector->objects_array[i].polies_array[0].vertices_array[1].y}}))
		{
			if (sector->objects_array[i].portal >= 0)
				return (sector->objects_array[i].portal);
			else
				return (-1);
		}
		i++;
	}
	return (cursect);
}
