/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:12:11 by eharrag-          #+#    #+#             */
/*   Updated: 2019/10/21 14:32:07 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_hors(t_sdl *sdl)
{
	int x;
	int y;

	y = 0;
	while (y < GRID_SIZE_Y)
	{
		x = 0;
		while (x < GRID_SIZE_X - 1)
		{
			x++;
			SDL_RenderDrawLine(sdl->renderer,
						sdl->grid_field[(y * GRID_SIZE_X + x) - 1].x,
						sdl->grid_field[(y * GRID_SIZE_X + x) - 1].y,
						sdl->grid_field[(y * GRID_SIZE_X + x)].x,
						sdl->grid_field[(y * GRID_SIZE_X + x)].y);
		}
		y++;
	}
}

void	draw_verts(t_sdl *sdl)
{
	int x;
	int y;

	x = 0;
	while (x < GRID_SIZE_X)
	{
		y = 0;
		while (y < GRID_SIZE_Y - 1)
		{
			y++;
			SDL_RenderDrawLine(sdl->renderer,
						sdl->grid_field[(y * GRID_SIZE_X + x) - GRID_SIZE_X].x,
						sdl->grid_field[(y * GRID_SIZE_X + x) - GRID_SIZE_X].y,
						sdl->grid_field[(y * GRID_SIZE_X + x)].x,
						sdl->grid_field[(y * GRID_SIZE_X + x)].y);
		}
		x++;
	}
}

void	draw_grid(t_sdl *sdl)
{
	SDL_SetRenderDrawColor(sdl->renderer, 85, 26, 139, 0);
	draw_verts(sdl);
	draw_hors(sdl);
}
