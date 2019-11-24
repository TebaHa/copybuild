/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:07:11 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 14:09:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		run_game_init_logic(t_game *fps)
{
	fps->logic.thread_end_index = 0;
	fps->logic.thread_start_index = 0;
	fps->logic.init = 0;
}

void		run_game(t_game *fps)
{
	run_game_init_logic(fps);
	while (1)
	{
		if (fps->eng->ending == true)
			break ;
		SDL_ShowCursor(SDL_DISABLE);
		game_movement_check(fps);
		if (SDL_PollEvent(&fps->eng->event))
		{
			if (fps->eng->grav == true)
				sound_player_control(&fps->player);
			if (fps->eng->event.type == SDL_QUIT)
				game_quit(fps);
			if (fps->eng->event.key.keysym.sym == SDLK_ESCAPE)
			{
				game_stop_threads(fps->render_thread_pool,
				THREAD_POOL_SIZE);
				break ;
			}
			game_buttons_control_up_main(fps);
			game_buttons_control_down_main(fps);
		}
		run_render(fps);
	}
}

void		run_render(t_game *fps)
{
	engine_run_doors(fps->eng, fps->eng->doors);
	apply_gravitation(fps);
	fire_anim_change(fps->eng, &fps->player);
	game_apply_movement_main(fps);
	game_threads_recount(fps);
	SDL_Delay(3);
}
