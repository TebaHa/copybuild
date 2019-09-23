/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:32:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/23 21:43:27 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		game_create_test_player(t_player *plr)
{
	plr->position = (t_point_3d){0, -300.0f, 0.f, 200.0f};
	plr->velocity = (t_point_3d){0, 0.f, 0.f, 0.f};
	plr->cursector = 1;
	plr->angle = 0;
	plr->real_position = (t_point_3d){0, -300.0f, 0.f, 200.0f};
	plr->sinangle = sinf(plr->angle);
	plr->cosangle = cosf(plr->angle);
	plr->controller.wasd[0] = 0;
	plr->controller.wasd[1] = 0;
	plr->controller.wasd[2] = 0;
	plr->controller.wasd[3] = 0;
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
}

static	int		game_thread_wrapper(void *ptr)
{
	t_game *fps;

	fps = (t_game *)ptr;
	engine_render_world(fps->eng, fps->player, fps->render_thread_pool[fps->thread_num].surface);
	SDL_Delay(5);
	return (fps->thread_num);
}

void			game_init_threads(t_thread_pool *render_thread_pool)
{
	int			i;

	i = 0;

	while (i < THREAD_POOL_SIZE)
	{
		render_thread_pool[i++].surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, (Uint32)0xff000000,
							(Uint32)0x00ff0000, (Uint32)0x0000ff00, (Uint32)0x000000ff);
	}
}

int		main(void)
{
	t_game			fps;
	int				dz;
	int				duck_shift;
	int				movement_dz;
	int				counter;
	int				thread_start_index;
	int				thread_end_index;
	int				init;

	movement_dz = 30;
	counter = 0;
	duck_shift = 0;
	thread_end_index = 0;
	thread_start_index = 0;
	init = 0;
	engine_sdl_init(&fps.eng);
	game_create_test_player(&fps.player);
	engine_create_world_from_file(fps.eng, GAME_PATH);
	game_init_threads(fps.render_thread_pool);
	SDL_ShowCursor(SDL_DISABLE);
	fps.eng->x = 0;
	fps.eng->y = 0;
	float yaw = 0;
	while (1)
	{
		fps.thread_num = thread_start_index;
		fps.render_thread_pool[thread_start_index].thread = SDL_CreateThread(game_thread_wrapper, NULL, (void *)&fps);
		if (fps.player.controller.moving)
		{
			float px = fps.player.position.x, py = fps.player.position.y;
			float dx = fps.player.velocity.x, dy = fps.player.velocity.y;
			int sect;
			int	sectprev;
			sectprev = fps.player.cursector;
			if((sect = engine_object_get_sector(fps.eng->world, (t_point_3d){0.f, px + dx, py + dy, 0.f}, fps.player.cursector)) >= 0)
			{
				if (fps.eng->world->sectors_array[sect].floor - duck_shift <= fps.player.position.z + KneeHeight - 50)
					move_player(fps.eng, &fps.player, dx, dy, sect);
			}
		}
		else
			counter = 0;
		if (fps.player.position.z > fps.eng->world->sectors_array[fps.player.cursector].floor + duck_shift + 100
		|| fps.player.position.z < fps.eng->world->sectors_array[fps.player.cursector].floor + duck_shift + 100)
			fps.player.controller.falling = 1;
		if (SDL_PollEvent(&fps.eng->event))
		{
			if (fps.eng->event.type == SDL_QUIT)
			{
				game_stop_threads(fps.render_thread_pool, THREAD_POOL_SIZE);
				break;
			}
			if (fps.eng->event.button.type == SDL_MOUSEBUTTONDOWN)
				if (fps.eng->event.button.button == SDL_BUTTON_LEFT)
				{
					fps.player.shoot = 1;
					fps.player.plr_state = P_FIRE;
				}
			if (fps.eng->event.button.type == SDL_MOUSEBUTTONUP)
				if (fps.eng->event.button.button == SDL_BUTTON_LEFT)
				{
					fps.player.shoot = 0;
					fps.player.firetime = FIRERATE;
				}
			if (fps.eng->event.type == SDL_KEYUP)
			{
				if (fps.eng->event.key.keysym.sym == SDLK_LSHIFT)
					fps.player.controller.running = 5;
				if (fps.eng->event.key.keysym.sym == SDLK_w)
					fps.player.controller.wasd[0] = 0;
				if (fps.eng->event.key.keysym.sym == SDLK_s)
					fps.player.controller.wasd[3] = 0;
				if (fps.eng->event.key.keysym.sym == SDLK_a)
					fps.player.controller.wasd[2] = 0;
				if (fps.eng->event.key.keysym.sym == SDLK_d)
					fps.player.controller.wasd[1] = 0;
			}
			if (fps.eng->event.type == SDL_KEYDOWN)
			{
				if (fps.eng->event.key.keysym.sym == SDLK_o)
					change_floor(fps.eng, fps.player.cursector, 10);
				if (fps.eng->event.key.keysym.sym == SDLK_l)
					change_floor(fps.eng, fps.player.cursector, -10);
				if (fps.eng->event.key.keysym.sym == SDLK_u)
					change_ceil(fps.eng, fps.player.cursector, 10);
				if (fps.eng->event.key.keysym.sym == SDLK_j)
					change_ceil(fps.eng, fps.player.cursector, -10);
				if (fps.eng->event.key.keysym.sym == SDLK_LSHIFT)
					fps.player.controller.running = 10;
				if (fps.eng->event.key.keysym.sym == SDLK_ESCAPE)
				{
					game_stop_threads(fps.render_thread_pool, THREAD_POOL_SIZE);
					break;
				}
				if (fps.eng->event.key.keysym.sym == SDLK_w)
					fps.player.controller.wasd[0] = 1;
				if (fps.eng->event.key.keysym.sym == SDLK_s)
					fps.player.controller.wasd[3] = 1;
				if (fps.eng->event.key.keysym.sym == SDLK_a)
					fps.player.controller.wasd[2] = 1;
				if (fps.eng->event.key.keysym.sym == SDLK_d)
					fps.player.controller.wasd[1] = 1;
				if (fps.eng->event.key.keysym.sym == SDLK_c)
				{
					if (fps.player.controller.ducking == 1)
					{
						duck_shift = 50;
						fps.player.controller.running -= 3;
						fps.player.controller.ducking = -1;
						fps.player.controller.falling  = 1;
					}
					else if (fps.player.controller.ducking == -1)
					{
						duck_shift = 0;
						fps.player.controller.running += 3;
						fps.player.controller.ducking = 1;
						fps.player.position.z += 50;
					}
				}
				if (fps.eng->event.key.keysym.sym == SDLK_SPACE && fps.player.controller.falling != 1)
				{
					if (fps.player.controller.ducking == -1)
					{
						fps.player.controller.running += 3;
						duck_shift = 0;
						fps.player.position.z = fps.eng->world->sectors_array[fps.player.cursector].floor + 100 - duck_shift;
						fps.player.controller.ducking = 1;
					}
					else
					{
						fps.player.controller.falling = 1;
						if ((fps.player.position.z + 150) >= fps.eng->world->sectors_array[fps.player.cursector].ceil)
						{
							fps.player.position.z += fps.eng->world->sectors_array[fps.player.cursector].ceil - fps.player.position.z - HeadMargin;
						}
						else
							fps.player.position.z += 150;
					}
				}
			}
		}
		if (fps.player.controller.falling == 1)
		{
				fps.player.position.z -= dz;
				dz += 2;
				if (fps.eng->world->sectors_array[fps.player.cursector].floor + 100 - duck_shift > fps.player.position.z)
				{
					fps.player.controller.falling = 0;
					fps.player.position.z = fps.eng->world->sectors_array[fps.player.cursector].floor + 100 - duck_shift;
					dz = 0;
				}
		}
		if (fps.player.shoot == 1)
		{
			fps.player.firetime = FIRERATE;
			shoot(fps.eng, fps.render_thread_pool[thread_end_index].surface, &fps.player, 1000);
		}
		if (fps.player.firetime != 0)
		{
			fps.player.firetime--;
		}
		else
			fps.player.plr_state = P_IDLE;
		t_fix_point_2d xy;
		get_relative_xy(fps.eng, &xy);
		fps.player.angle += xy.x * 0.02f;
		yaw = clamp(yaw - xy.y * 0.02f, -5, 5);
		fps.player.yaw = yaw - fps.player.velocity.z * 0.5f;
		move_player(fps.eng, &fps.player, 0, 0, fps.player.cursector);
		float move_vec[2] = {0.f, 0.f};
		if(fps.player.controller.wasd[0])
		{
			move_vec[0] += fps.player.cosangle * fps.player.controller.running;
			move_vec[1] += fps.player.sinangle * fps.player.controller.running;
		}
		if(fps.player.controller.wasd[1])
		{
			move_vec[0] -= fps.player.sinangle * fps.player.controller.running;
			move_vec[1] += fps.player.cosangle * fps.player.controller.running;
		}
		if(fps.player.controller.wasd[2])
		{
			move_vec[0] += fps.player.sinangle * fps.player.controller.running;
			move_vec[1] -= fps.player.cosangle * fps.player.controller.running;
		}
		if(fps.player.controller.wasd[3])
		{
			move_vec[0] -= fps.player.cosangle * fps.player.controller.running;
			move_vec[1] -= fps.player.sinangle * fps.player.controller.running;
		}
		int pushing = fps.player.controller.wasd[0] || fps.player.controller.wasd[1] || fps.player.controller.wasd[2] || fps.player.controller.wasd[3];
		float acceleration = pushing ? 0.4 : 0.2;
		fps.player.velocity.x = fps.player.velocity.x * (1 - acceleration) + move_vec[0] * acceleration;
		fps.player.velocity.y = fps.player.velocity.y * (1 - acceleration) + move_vec[1] * acceleration;
		if (pushing)
			fps.player.controller.moving = 1;
		else
			fps.player.controller.moving = 0;
		if (thread_start_index == (THREAD_POOL_SIZE - 1) || init == 1)
		{
			SDL_WaitThread(fps.render_thread_pool[thread_end_index].thread, &fps.render_thread_pool[thread_end_index].value);
			engine_draw_hud(fps.eng, &fps.player, fps.render_thread_pool[thread_end_index].surface);
			engine_render_frame(fps.eng, fps.render_thread_pool[thread_end_index].surface);
			thread_start_index = thread_end_index;
			thread_end_index = thread_end_index < (THREAD_POOL_SIZE - 1) ? thread_end_index + 1 : 0;
			if (init == 0)
				init = 1;
		}
		else
			thread_start_index++;
		fps.player.anim += 1;
	}
	engine_sdl_uninit(fps.eng);
	return (0);
}

void	game_stop_threads(t_thread_pool	*render_thread, int thread_count)
{
	int	i;

	i = 0;
	while (i < thread_count)
	{
		SDL_WaitThread(render_thread[i].thread, &render_thread[i].value);
		i++;
	}
}

void	move_player(t_engine *eng, t_player *plr, float dx, float dy, unsigned sect)
{
	plr->position.x += dx;
	plr->position.y += dy;
	plr->cursector = sect;
	plr->sinangle = sinf(plr->angle);
	plr->cosangle = cosf(plr->angle);
}

void	change_floor(t_engine *eng, int sect, int change)
{
	eng->world->sectors_array[sect].floor += change;
}

void	change_ceil(t_engine *eng, int sect, int change)
{
	eng->world->sectors_array[sect].ceil += change;
}
