/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:05:37 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 20:55:53 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_sdl	*init_editor(void)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	init_sdl(sdl);
	init_grid(sdl->grid_field);
	return (sdl);
}

void	run_editor(t_sdl *sdl)
{
	sdl->window = SDL_CreateWindow("editor", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, SIZE_WIN_X, SIZE_WIN_Y,
					SDL_WINDOW_OPENGL);
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
					SDL_RENDERER_ACCELERATED);
	redraw(sdl);
	SDL_RenderPresent(sdl->renderer);
	big_loop(sdl);
	SDL_DestroyWindow(sdl->window);
	SDL_DestroyRenderer(sdl->renderer);
}

void	stop_editor(t_sdl *sdl)
{
	SDL_DestroyWindow(sdl->window);
}
