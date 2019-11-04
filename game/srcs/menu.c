/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:49:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/04 20:03:08 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		game_menu_quit(t_game *fps)
{
	SDL_Delay(50);
	game_stop_threads(fps->render_thread_pool,
	1);
	engine_sdl_uninit(fps->eng);
	close_game(0);
}

void	game_render_menu(t_menu *menu, SDL_Surface *surf)
{
	int	i;

	i = 0;
	draw_from_surface_to_surface(surf, menu->background->surface[0], 0, 0);
	while (i < 5)
	{
		draw_from_surface_to_surface(surf, menu->button[i]->normal->surface[0],
		menu->button[i]->position.x, menu->button[i]->position.y);
		i++;
	}
}

void	game_find_button()
{

}

void	game_menu_main(t_game *fps)
{
	SDL_ShowCursor(SDL_ENABLE);
	while (1)
	{
		SDL_GetMouseState(&fps->eng->x, &fps->eng->y);
		game_find_button(fps);
		game_render_menu(fps->eng->menu, fps->render_thread_pool[0].surface);
		if (SDL_PollEvent(&fps->eng->event))
		{
			if (fps->eng->event.type == SDL_QUIT)
				game_menu_quit(fps);
			if (fps->eng->event.type == SDL_KEYDOWN)
			{
				if (fps->eng->event.key.keysym.sym == SDLK_ESCAPE)
				game_menu_quit(fps);
			}
		}
		engine_render_frame(fps->eng,
		fps->render_thread_pool[fps->logic.thread_end_index].surface);
		engine_present_and_clear_frame(fps->eng);
	}
}

