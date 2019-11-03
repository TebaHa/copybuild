/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_collision_detector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 10:48:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/03 17:24:23 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

int		line_intersection_check(t_line_2d plr_dir, t_line_2d wall_dir)
{
	if (intersect_box(plr_dir.a, plr_dir.b,
	wall_dir.a, wall_dir.b)
	&& (point_side(plr_dir.b,
	wall_dir.a, wall_dir.b) < 0))
		return (1);
	return (0);

}

void	count_heights(float *hole_low, float *hole_high,
		t_sector *sector)
{
	*hole_low = max(sector->floor,
	sector->floor);
	*hole_high = min(sector->ceil,
	sector->ceil);
}

int		check_wall_passed(t_engine *eng, t_player *plr,
		t_line_2d plr_dir, int *moving)
{
	int			i;
	float		hole_low;
	float		hole_high;
	t_sector	*sector;

	i = 0;
	sector = &eng->world->sectors_array[plr->cursector];
	hole_low = 9e9;
	hole_high = -9e9;
	while (i < sector->objects_count)
	{
		if (line_intersection_check(plr_dir,
		(t_line_2d){(t_point_2d){
		sector->objects_array[i].polies_array[0].vertices_array[0].x,
		sector->objects_array[i].polies_array[0].vertices_array[0].y
		},
		(t_point_2d){
		sector->objects_array[i].polies_array[0].vertices_array[1].x,
		sector->objects_array[i].polies_array[0].vertices_array[1].y
		}}))
		{
			if (sector->objects_array[i].portal >= 0)
				count_heights(&hole_low, &hole_high,
				&eng->world->sectors_array[sector->objects_array[i].portal]);
			if(hole_high < plr->position.z + HEAD_MARGIN
			|| hole_low  > plr->position.z - EYE_HEIGHT + KNEE_HEIGHT)
			{
				vector_projection(plr,
				sector->objects_array[i].polies_array[0].vertices_array[0],
				sector->objects_array[i].polies_array[0].vertices_array[1]);
				*moving = 0;
			}
		}
		i++;
	}
	return (plr->cursector);
}

void	vector_projection(t_player *plr, t_point_3d v1, t_point_3d v2)
{
	float	xd;
	float	yd;
	float	dx;
	float	dy;

	xd = v2.x - v1.x;
	yd = v2.y - v1.y;
	dx = plr->velocity.x;
	dy = plr->velocity.y;
	plr->velocity.x = xd * (dx * xd + dy * yd)
	/ (xd * xd + yd * yd);
	plr->velocity.y = yd * (dx * xd + dy * yd)
	/ (xd * xd + yd * yd);
}
