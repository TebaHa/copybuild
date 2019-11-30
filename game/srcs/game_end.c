/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:47:00 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 14:09:19 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	game_quit(t_game *fps)
{
	fps->work.work = false;
	SDL_Delay(50);
}

void	game_end(t_game *fps)
{
	SDL_ShowCursor(SDL_DISABLE);
	while (1)
	{
		if (SDL_PollEvent(&fps->eng->event))
		{
			if (fps->eng->event.button.type
			== SDL_MOUSEBUTTONDOWN)
			{
				game_quit(fps);
				break ;
			}
		}
		game_render_endframe(fps->menu,
		fps->render_thread_pool[0].surface);
		engine_render_frame(fps->eng,
		fps->render_thread_pool[0].surface);
		engine_present_and_clear_frame(fps->eng);
	}
}

void	game_render_endframe(t_menu *menu, SDL_Surface *surf)
{
	draw_from_surface_to_surface(surf,
	menu->background->surface[0], 0,
	0);
	draw_from_surface_to_surface(surf,
	menu->element[ME_ENDGAME]->sprite->surface[0], (WIDTH -
	menu->element[ME_ENDGAME]->sprite->surface[0]->w) / 2,
	(HEIGHT -
	menu->element[ME_ENDGAME]->sprite->surface[0]->h) / 2);
}
