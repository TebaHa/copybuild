/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:32:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/12 18:13:48 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		game_create_test_player(t_player *plr)
{
	plr->position = (t_point_3d){0, 0, 20};
	plr->velocity = (t_point_3d){0, 0, 0};
	plr->cursector = 0;
	plr->angle = 10;
	plr->controller.wasd[0] = 0;
	plr->controller.wasd[1] = 0;
	plr->controller.wasd[2] = 0;
	plr->controller.wasd[3] = 0;
	plr->controller.ducking = 0;
	plr->controller.falling = 0;
	plr->controller.ground = 1;
	plr->controller.moving = 0;
}

int		main(void)
{
	t_game	fps;

	engine_sdl_init(&fps.eng);
	sdl_clear_window(fps.eng->ren);
	game_create_test_player(&fps.player);
	engine_create_test_world(&fps.eng->world);
	engine_render_sector(fps.eng, &fps.eng->world->sectors_array[0], &fps.player);
	engine_render_frame(fps.eng);
	while (1)
	{
		if (SDL_PollEvent(&fps.eng->event))
		{
			if (fps.eng->event.type == SDL_KEYDOWN)
			{
				if (fps.eng->event.key.keysym.sym == SDLK_ESCAPE)
					break;
				if (fps.eng->event.key.keysym.sym == SDLK_w)
					fps.player.position.x++;
				if (fps.eng->event.key.keysym.sym == SDLK_s)
					fps.player.position.y++;
				if (fps.eng->event.key.keysym.sym == SDLK_a)
					fps.player.angle += 5;
				if (fps.eng->event.key.keysym.sym == SDLK_c)
				{
					if (fps.player.controller.ducking == 0)
					{
						fps.player.controller.ducking = 1;
						fps.player.position.z -= 15;
					}
					else if (fps.player.controller.ducking == 1)
					{
						fps.player.controller.ducking = 0;
						fps.player.position.z += 15;
					}
				}
			}
		}
		sdl_clear_window(fps.eng->ren);
		engine_render_sector(fps.eng, &fps.eng->world->sectors_array[0], &fps.player);
		engine_render_frame(fps.eng);
	}
	engine_sdl_uninit(fps.eng);
	return (0);
}
