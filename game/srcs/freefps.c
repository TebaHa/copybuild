/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:32:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/04 19:04:18 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		game_create_test_player(t_player *plr)
{
	plr->position = (t_point_3d){0, 750.0f, 750.0f, 100.0f};
	plr->velocity = (t_point_3d){0, 0.f, 0.f, 0.f};
	plr->cursector = 0;
	plr->angle = 0;
	plr->sinangle = sinf(plr->angle);
	plr->cosangle = cosf(plr->angle);
	plr->controller.wasd[0] = 0;
	plr->controller.wasd[1] = 0;
	plr->controller.wasd[2] = 0;
	plr->controller.wasd[3] = 0;
	plr->controller.ducking = 0;
	plr->controller.falling = 0;
	plr->controller.ground = 1;
	plr->controller.moving = 0;
	plr->controller.running = 10;
	plr->yaw = 5;
}

int		main(void)
{
	t_game	fps;
	int		*rendered;

	rendered = (int *)ft_memalloc(sizeof(int) * 2);
	engine_sdl_init(&fps.eng);
	game_create_test_player(&fps.player);
	engine_create_world_from_file(fps.eng, "../game/resources/1.lvl");
	SDL_ShowCursor(SDL_DISABLE);
	float yaw = 0;
	while (1)
	{
		rendered[0] = 0;
		rendered[1] = 0;
		SDL_SetRenderDrawColor(fps.eng->ren, 0, 0, 0, 255);
		SDL_RenderClear(fps.eng->ren);
		engine_render_world(fps.eng, &fps.player, rendered);
		SDL_RenderPresent(fps.eng->ren);
		if (fps.player.position.z > fps.eng->world->sectors_array[fps.player.cursector].floor + 100)
			fps.player.controller.falling = 1;
		if (fps.player.controller.moving)
		{
			float dx = fps.player.velocity.x, dy = fps.player.velocity.y;
			int sect = engine_object_get_sector(fps.eng->world, (t_point_3d) {0, fps.player.position.x + dx, fps.player.position.y + dy, 0});
			if (sect >= 0)
			{
				fps.player.position.x += dx;
				fps.player.position.y += dy;
				fps.player.cursector = sect;
			}
		}
		if (SDL_PollEvent(&fps.eng->event))
		{
			if (fps.eng->event.type == SDL_KEYUP)
			{
				if (fps.eng->event.key.keysym.sym == SDLK_LSHIFT)
					fps.player.controller.running = 10;
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
					fps.player.controller.running = 15;
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
				{
					if (fps.player.controller.ducking == 0 && fps.player.controller.falling != 1)
					{
						fps.player.controller.ducking = 1;
						fps.player.position.z -= 50;
					}
					else if (fps.player.controller.ducking == 1 && fps.player.controller.falling != 1)
					{
						fps.player.controller.ducking = 0;
						fps.player.position.z += 50;
					}
				}
				if (fps.eng->event.key.keysym.sym == SDLK_SPACE && fps.player.controller.falling != 1)
				{
					fps.player.position.z += 100;
					fps.player.controller.falling = 1;
					if (fps.player.controller.ducking == 1)
						fps.player.controller.ducking = 0;
				}
			}
		}
		if (fps.player.controller.falling == 1)
		{
			if (fps.player.position.z == fps.eng->world->sectors_array[fps.player.cursector].floor + 100)
				fps.player.controller.falling = 0;
			else
				fps.player.position.z -= 5;
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
		int pushing = fps.player.controller.wasd[0] || fps.player.controller.wasd[1] || fps.player.controller.wasd[2] || fps.player.controller.wasd[3];
		float acceleration = pushing ? 0.4 : 0.2;
		fps.player.velocity.x = fps.player.velocity.x * (1 - acceleration) + move_vec[0] * acceleration;
		fps.player.velocity.y = fps.player.velocity.y * (1 - acceleration) + move_vec[1] * acceleration;
		if (pushing)
			fps.player.controller.moving = 1;
		else
			fps.player.controller.moving = 0;
		engine_clear_frame(fps.eng);
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
