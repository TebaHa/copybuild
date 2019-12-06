/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points_of_sect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:17:33 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:58:45 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	last_point(t_sdl *sdl, t_ed_sector *sector, t_walls *walls, int i)
{
	if (sector->size > 2 &&
		((sdl->mouse_position.x >= sector->point[0].x - POINT_SIZE / 2 &&
		sdl->mouse_position.x <= sector->point[0].x + POINT_SIZE / 2) &&
		(sdl->mouse_position.y >= sector->point[0].y - POINT_SIZE / 2 &&
		sdl->mouse_position.y <= sector->point[0].y + POINT_SIZE / 2)))
	{
		if (check_local_intersection(sdl, sector, walls) < 3 &&
			is_clockwise(walls))
		{
			cut_the_rope(sdl, sector, i);
			add_point(sdl, sector, i);
			sector->num_of_sector = sdl->count;
			sdl->count++;
			sector->next = init_sector();
			sector = sector->next;
		}
	}
}

int		dot_in_used(t_ed_sector *sector, int x, int y)
{
	int i;

	i = 0;
	while (i < sector->size)
	{
		if (sector->point[i].x == x && sector->point[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

void	mid_points(t_sdl *sdl, t_ed_sector *sector, t_walls *walls, int i)
{
	if (sector->size > 0 &&
		dot_in_used(sector, sdl->grid_field[i].x, sdl->grid_field[i].y) == 0 &&
		check_local_intersection(sdl, sector, walls) < 2)
	{
		if (sector->size > 1)
		{
			if (is_clockwise(walls))
			{
				cut_the_rope(sdl, sector, i);
				add_point(sdl, sector, i);
			}
		}
		else
		{
			cut_the_rope(sdl, sector, i);
			add_point(sdl, sector, i);
		}
	}
}

void	which_of_points(t_sdl *sdl, t_ed_sector *sector, t_walls *walls, int i)
{
	if (sector->size == 0)
		add_point(sdl, sector, i);
	else
	{
		mid_points(sdl, sector, walls, i);
		last_point(sdl, sector, walls, i);
	}
}
