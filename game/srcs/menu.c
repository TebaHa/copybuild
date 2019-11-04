/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:49:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/03 14:38:17 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	game_render_menu(void)
{
//	return (0);
}

void	game_menu_main(t_game *fps)
{
	while (1)
	{
		game_render_menu();
		if (SDL_PollEvent(&fps->eng->event))
		{
			if (fps->eng->event.type == SDL_QUIT)
				game_quit(fps);
			if (fps->eng->event.type == SDL_KEYDOWN)
			{
				if (fps->eng->event.key.keysym.sym == SDLK_ESCAPE)
				game_quit(fps);
			}
		}
	}
}

// В freefps дубликат
//void	game_quit(t_game *fps)
//{
//	game_stop_threads(fps->render_thread_pool,
//	THREAD_POOL_SIZE);
//	engine_sdl_uninit(fps->eng);
//	close_game(0);
//}
