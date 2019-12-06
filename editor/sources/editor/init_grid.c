/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 15:04:11 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:48:00 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		check_the_grid(t_ed_point *grid_field, int x, int y)
{
	int i;

	i = 0;
	while (i < GRID_SIZE)
	{
		if (x <= grid_field[i].x + POINT_SIZE / 2 &&
				x >= grid_field[i].x - POINT_SIZE / 2 &&
				y <= grid_field[i].y + POINT_SIZE / 2 &&
				y >= grid_field[i].y - POINT_SIZE / 2)
			return (i);
		i++;
	}
	return (-1);
}

void	save_the_grid(t_ed_point *grid_field, SDL_Rect grid)
{
	int i;
	int x;
	int y;

	i = 0;
	y = grid.y;
	while (i < GRID_SIZE)
	{
		while (y < grid.y + grid.h)
		{
			x = grid.x;
			while (x < grid.x + grid.w)
			{
				grid_field[i].x = x;
				grid_field[i].y = y;
				x += STEP;
				i++;
			}
			y += STEP;
		}
	}
}

void	init_grid(t_ed_point *grid_field)
{
	SDL_Rect	grid;

	grid.x = 94;
	grid.y = 101;
	grid.w = (int)SIZE_WIN_X * 0.8 - grid.x * 2 + 1;
	grid.h = SIZE_WIN_Y - grid.y * 2 + 1;
	save_the_grid(grid_field, grid);
}
