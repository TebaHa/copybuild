/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:32:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/15 10:32:07 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		game_create_test_player(t_player *plr)
{
	plr->position = (t_point_3d){0, 0, 60};
	plr->velocity = (t_point_3d){0, 0, 0};
	plr->cursector = 1;
	plr->angle = 10;
	plr->controller.wasd[0] = 0;
	plr->controller.wasd[1] = 0;
	plr->controller.wasd[2] = 0;
	plr->controller.wasd[3] = 0;
	plr->controller.ducking = 0;
	plr->controller.falling = 0;
	plr->controller.ground = 1;
	plr->controller.moving = 0;
	plr->controller.running = 0;
	plr->yaw = 1;
}

int		main(void)
{
	t_game	fps;
	int		*rendered;

	rendered = (int *)ft_memalloc(sizeof(int) * 2);
	engine_sdl_init(&fps.eng);
	game_create_test_player(&fps.player);
	engine_create_test_world(&fps.eng->world);
	SDL_ShowCursor(SDL_DISABLE);
	float yaw = 0;
	while (1)
	{
		rendered[0] = 0;
		rendered[1] = 0;
		engine_render_sector(fps.eng, &fps.eng->world->sectors_array[1], &fps.player, rendered);
		engine_render_frame(fps.eng);
		if (SDL_PollEvent(&fps.eng->event))
		{
			if (fps.eng->event.type == SDL_KEYUP)
			{
				if (fps.eng->event.key.keysym.sym == SDLK_LSHIFT)
					fps.player.controller.running 	= 0;
			}
			if (fps.eng->event.type == SDL_KEYDOWN)
			{
				fps.player.controller.moving = 0;
				if (fps.eng->event.key.keysym.sym == SDLK_LSHIFT)
					fps.player.controller.running = 3;
				if (fps.eng->event.key.keysym.sym == SDLK_ESCAPE)
					break;
				if (fps.eng->event.key.keysym.sym == SDLK_w)
				{
					fps.player.controller.moving = 1;
					float dx = cosf(fps.player.angle) * (3 + fps.player.controller.running);
					float dy = sinf(fps.player.angle) * (3 + fps.player.controller.running);
					int sect = engine_object_get_sector(fps.eng->world, (t_point_3d) {fps.player.position.x + dx, fps.player.position.y + dy, 0});
					if (sect >= 0)
					{
						fps.player.position.x += dx;
						fps.player.position.y += dy;
						fps.player.cursector = sect;
					}
				}
				if (fps.eng->event.key.keysym.sym == SDLK_s)
				{
					fps.player.controller.moving = 1;
					float dx = cosf(fps.player.angle) * 3;
					float dy = sinf(fps.player.angle) * 3;
					int sect = engine_object_get_sector(fps.eng->world, (t_point_3d) {fps.player.position.x - dx, fps.player.position.y - dy, 0});
					if (sect >= 0)
					{
						fps.player.position.x -= dx;
						fps.player.position.y -= dy;
						fps.player.cursector = sect;
					}
				}
				if (fps.eng->event.key.keysym.sym == SDLK_a)
				{
					fps.player.controller.moving = 1;
					float dx = sinf(fps.player.angle) * 3;
					float dy = cosf(fps.player.angle) * 3;
					int sect = engine_object_get_sector(fps.eng->world, (t_point_3d) {fps.player.position.x + dx, fps.player.position.y - dy, 0});
					if (sect >= 0)
					{
						fps.player.position.x += dx;
						fps.player.position.y -= dy;
						fps.player.cursector = sect;
					}
				}
				if (fps.eng->event.key.keysym.sym == SDLK_d)
				{
					fps.player.controller.moving = 1;
					float dx = sinf(fps.player.angle) * 3;
					float dy = cosf(fps.player.angle) * 3;
					int sect = engine_object_get_sector(fps.eng->world, (t_point_3d) {fps.player.position.x - dx, fps.player.position.y + dy, 0});
					if (sect >= 0)
					{
						fps.player.position.x -= dx;
						fps.player.position.y += dy;
						fps.player.cursector = sect;
					}
				}
				if (fps.eng->event.key.keysym.sym == SDLK_c)
				{
					if (fps.player.controller.ducking == 0)
					{
						fps.player.controller.ducking = 1;
						fps.player.position.z -= 20;
					}
					else if (fps.player.controller.ducking == 1)
					{
						fps.player.controller.ducking = 0;
						fps.player.position.z += 20;
					}
				}
				if (fps.eng->event.key.keysym.sym == SDLK_SPACE && fps.player.controller.falling != 1)
				{
					fps.player.position.z += 30;
					fps.player.controller.falling = 1;
				}
			}
		}
		if (fps.player.controller.falling == 1)
		{
			fps.player.position.z -= 2;
			if (fps.player.position.z == 60)
				fps.player.controller.falling = 0;
		}
		int x, y;
		SDL_GetRelativeMouseState(&x, &y);
		fps.player.angle += x * 0.03f;
		yaw = clamp(yaw - y * 0.05f, -5, 5);
		fps.player.yaw = yaw - fps.player.velocity.z * 0.5f;
	}
	engine_sdl_uninit(fps.eng);
	return (0);
}
