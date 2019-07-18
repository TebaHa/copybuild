/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:41:43 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/18 17:13:36 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_sdl_init(t_engine **eng)
{
	*eng = (t_engine *)ft_memalloc(sizeof(t_engine));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error_handler("SDL_Init Error: ", SDL_GetError(), (*eng));
	(*eng)->win = SDL_CreateWindow("doka 2", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if ((*eng)->win == NULL)
		error_handler("SDL_CreateWindow Error: ", SDL_GetError(), (*eng));
	(*eng)->ren = SDL_CreateRenderer((*eng)->win, -1, SDL_RENDERER_ACCELERATED);
	if ((*eng)->ren == NULL)
		error_handler("SDL_CreateRenderer Error: ", SDL_GetError(), (*eng));
	(*eng)->surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, (Uint32)0xff000000,
							(Uint32)0x00ff0000, (Uint32)0x0000ff00, (Uint32)0x000000ff);
	if ((*eng)->surface == NULL)
		error_handler("SDL_CreateSurface Error: ", SDL_GetError(), (*eng));
}

void		engine_sdl_uninit(t_engine *eng)
{
	SDL_DestroyRenderer(eng->ren);
	SDL_DestroyWindow(eng->win);
	SDL_Quit();
}
