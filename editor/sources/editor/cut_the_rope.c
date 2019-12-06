/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_the_rope.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:43:08 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:51:55 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	get_conditional_by_status(int status, int j)
{
	if (status == 1)
	{
		if (j > 0)
			return (1);
		else
			return (0);
	}
	else if (status == 0)
	{
		if (j < GRID_SIZE)
			return (1);
		else
			return (0);
	}
	return (-1);
}

/*
**	x1 = sector->point[sector->size - 1].x;
**	y1 = sector->point[sector->size - 1].y;
**	x2 = sdl->grid_field[i].x;
**	y2 = sdl->grid_field[i].y;
**	check_x = sdl->grid_field[j].x;
**	check_y = sdl->grid_field[j].y;
**
**	if ((check_x - x1) * (y2 - y1) - (check_y - y1) * (x2 - x1) == 0)
**	{
**	if (((check_x > x1 && check_x < x2) || (check_x < x1 && check_x > x2)) ||
**	((check_y > y1 && check_y < y2) || (check_y < y1 && check_y > y2)))
*/

int			point_on_segment(t_ed_point *grid_field, t_ed_point *point, int j, int i)
{
	if (((grid_field[j].x > point->x && grid_field[j].x < grid_field[i].x) ||
		(grid_field[j].x < point->x && grid_field[j].x > grid_field[i].x)) ||
		((grid_field[j].y > point->y && grid_field[j].y < grid_field[i].y) ||
		(grid_field[j].y < point->y && grid_field[j].y > grid_field[i].y)))
		return (1);
	return (0);
}

int			points_on_line(t_ed_point *grid_field, t_ed_point *point, int j, int i)
{
	if ((grid_field[j].x - point->x) * (grid_field[i].y - point->y) -
			(grid_field[j].y - point->y) * (grid_field[i].x - point->x) == 0)
		return (1);
	return (0);
}

void		cut_the_rope(t_sdl *sdl, t_ed_sector *sector, int i)
{
	int j;
	int status;

	if (sector->point[sector->size - 1].y > sdl->grid_field[i].y ||
		sector->point[sector->size - 1].x > sdl->grid_field[i].x)
	{
		status = 1;
		j = GRID_SIZE;
	}
	else
	{
		status = 0;
		j = 0;
	}
	while (get_conditional_by_status(status, j))
	{
		if (points_on_line(sdl->grid_field, &sector->point[sector->size - 1],
			j, i) == 1)
		{
			if (point_on_segment(sdl->grid_field,
					&sector->point[sector->size - 1], j, i) == 1)
				add_point(sdl, sector, j);
		}
		j = status == 1 ? j - 1 : j + 1;
	}
}
