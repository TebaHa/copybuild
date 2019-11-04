/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:32:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/04 20:44:45 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		game_quit(t_game *fps)
{
	SDL_Delay(50);
	game_stop_threads(fps->render_thread_pool,
	THREAD_POOL_SIZE);
	engine_sdl_uninit(fps->eng);
	close_game(0);
}

void		game_init_player(t_player *plr)
{
	plr->velocity = (t_point_3d){0, 0.f, 0.f, 0.f};
	plr->cursector = 1;
	plr->angle = 0;
	plr->sinangle = sinf(plr->angle);
	plr->cosangle = cosf(plr->angle);
	plr->controller.ducking = 1;
	plr->controller.duckcheck = -1;
	plr->controller.falling = 0;
	plr->controller.ground = 1;
	plr->controller.moving = 0;
	plr->controller.running = 7;
	plr->controller.fakefall = 0;
	plr->plr_state = P_IDLE;
	plr->anim = 0;
	plr->yaw = 0;
	plr->shoot = 0;
	plr->delay = 3;
	plr->armor = 100;
	plr->health = 100;
	plr->steps_sound = sound_init("player_steps");
	initilize_abs_sprt_sizes(plr);
}

void		game_init(t_game *fps, int argc, char **argv)
{
	engine_sdl_init(&fps->eng);
	game_init_player(&fps->player);
	parser_game(fps, argc, argv);
	parser_engine(fps->eng, &fps->player);
	fps->player.cursector = engine_object_get_sector(fps->eng->world,
	(t_point_3d){0, fps->player.position.x,
	fps->player.position.y, fps->player.position.z},
	fps->player.cursector);
	prepare_polygones(fps->eng);
	game_init_threads(fps->render_thread_pool);
	SDL_ShowCursor(SDL_DISABLE);
	fps->logic.duck_shift = 0;
	fps->logic.thread_end_index = 0;
	fps->logic.thread_start_index = 0;
	fps->logic.init = 0;
	fps->logic.grav = 1;
	fps->logic.yaw = 0;
	fps->eng->x = 0;
	fps->eng->y = 0;
}

void		run_game(t_game *fps)
{
	while (1)
	{
		SDL_ShowCursor(SDL_DISABLE);
		game_movement_check(fps);
		if (SDL_PollEvent(&fps->eng->event))
		{
			sound_player_control(&fps->player);
			if (fps->eng->event.type == SDL_QUIT)
				game_quit(fps);
			game_buttons_control_up_main(fps);
			game_buttons_control_down_main(fps);
		}
		apply_gravitation(fps);
		fire_anim_change(fps->eng, &fps->player);
		game_apply_movement_main(fps);
		game_threads_recount(fps);
		SDL_Delay(3);
	}
}

int			main(int argc, char **argv)
{
	t_game			fps;

	game_init(&fps, argc, argv);
	game_menu_main(&fps);
	return (0);
}
