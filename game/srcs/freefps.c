/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:32:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/18 07:07:12 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		game_create_test_player(t_player *plr)
{
	plr->position = (t_point_3d){0, 75.0f, 75.0f, 100.0f};
	plr->velocity = (t_point_3d){0, 0.f, 0.f, 0.f};
	plr->cursector = 0;
	plr->angle = 0;
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
	plr->controller.running = 10;
	plr->controller.fakefall = 0;
	plr->yaw = 5;
}

int		main(void)
{
	t_game	fps;
	int		*rendered;
	int		dz;
	int		tz;
	int		movement_dz;
	int		counter;

	rendered = (int *)ft_memalloc(sizeof(int) * 2);
	movement_dz = 30;
	counter = 0;
	tz = 0;
	engine_sdl_init(&fps.eng);
	game_create_test_player(&fps.player);
	engine_create_world_from_file(fps.eng, "./game/resources/1.lvl");
	SDL_ShowCursor(SDL_DISABLE);
	float yaw = 0;
	while (1)
	{
		rendered[0] = 0;
		rendered[1] = 0;
		engine_render_world(fps.eng, &fps.player, rendered);
		engine_render_frame(fps.eng);
		if (fps.player.controller.moving)
		{
			float dx = fps.player.velocity.x, dy = fps.player.velocity.y;
			int sect = engine_object_get_sector(fps.eng->world, (t_point_3d) {0, fps.player.position.x + dx, fps.player.position.y + dy, 0});
			if (sect >= 0)
			{
				fps.player.position.x += dx;
				fps.player.position.y += dy;
				if (fps.player.controller.ducking == 1)
				{
					movement_dz = fabs(sin(M_PI_4 * counter++)) * 13;
					fps.player.position.z += movement_dz;
				}
				fps.player.cursector = sect;
			}
		}
		else
			counter = 0;
		if ((fps.player.position.z) > fps.eng->world->sectors_array[fps.player.cursector].floor + 100)
			fps.player.controller.falling = 1;
		if (SDL_PollEvent(&fps.eng->event))
		{
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
				if (fps.eng->event.key.keysym.sym == SDLK_LSHIFT)
					fps.player.controller.running = 10;
				if (fps.eng->event.key.keysym.sym == SDLK_ESCAPE)
					break;
				if (fps.eng->event.key.keysym.sym == SDLK_w)
					fps.player.controller.wasd[0] = 1;
				if (fps.eng->event.key.keysym.sym == SDLK_s)
					fps.player.controller.wasd[3] = 1;
				if (fps.eng->event.key.keysym.sym == SDLK_a)
					fps.player.controller.wasd[2] = 1;
				if (fps.eng->event.key.keysym.sym == SDLK_d)
					fps.player.controller.wasd[1] = 1;
				if (fps.eng->event.key.keysym.sym == SDLK_c)
					fps.player.controller.duckcheck = 1;
				if (fps.eng->event.key.keysym.sym == SDLK_SPACE && fps.player.controller.fakefall != 1)
				{
					if (fps.player.controller.ducking == -1)
					{
						fps.player.controller.ducking = 1;
						fps.player.controller.running += 4 * fps.player.controller.ducking;
						fps.player.position.z += 100 * fps.player.controller.ducking;
					}
					else
					{
						fps.player.controller.ducking = 1;
						fps.player.position.z += 150;
						fps.player.controller.fakefall = 1;
					}
				}
			}
		}
		if (fps.player.controller.falling == 1 || fps.player.controller.fakefall == 1)
		{
				fps.player.position.z -= dz;
				tz += dz;
				dz += 2;
				if (fps.eng->world->sectors_array[fps.player.cursector].floor + 100 > fps.player.position.z - dz)
				{
					fps.player.controller.falling = 0;
					fps.player.controller.fakefall = 0;
					fps.player.position.z = fps.eng->world->sectors_array[fps.player.cursector].floor + 100;
					tz = 0;
					dz = 0;
				}
		}
		int x, y;
		SDL_GetRelativeMouseState(&x, &y);
		fps.player.angle += x * 0.03f;
		yaw = clamp(yaw - y * 0.05f, -5, 5);
		fps.player.yaw = yaw - fps.player.velocity.z * 0.5f;
		fps.player.cosangle = cosf(fps.player.angle);
		fps.player.sinangle = sinf(fps.player.angle);
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
		if (fps.player.controller.duckcheck == 1)
		{
			fps.player.controller.ducking *= -1;
			fps.player.controller.duckcheck = -1;
			fps.player.controller.running += 4 * fps.player.controller.ducking;
			fps.player.position.z += 50 * fps.player.controller.ducking;
		}
		int pushing = fps.player.controller.wasd[0] || fps.player.controller.wasd[1] || fps.player.controller.wasd[2] || fps.player.controller.wasd[3];
		float acceleration = pushing ? 0.4 : 0.2;
		fps.player.velocity.x = fps.player.velocity.x * (1 - acceleration) + move_vec[0] * acceleration;
		fps.player.velocity.y = fps.player.velocity.y * (1 - acceleration) + move_vec[1] * acceleration;
		if (pushing)
			fps.player.controller.moving = 1;
		else
			fps.player.controller.moving = 0;
		engine_clear_frame(fps.eng);
		zbuffer_zero(fps.eng->z_buff);
		SDL_Delay(10);
	}
	engine_sdl_uninit(fps.eng);
	return (0);
}

/*
int		main(void)
{
	t_game	fps;

	engine_sdl_init(&fps.eng);
	engine_create_world_from_file(fps.eng, "game/resources/1.lvl");
	return (0);
}
 */
