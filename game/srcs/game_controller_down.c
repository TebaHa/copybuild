/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controller_down.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:30:28 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 17:00:48 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	game_buttons_control_down_main(t_game *fps)
{
	if (fps->eng->event.type == SDL_KEYDOWN)
	{
		game_buttons_control_down1(fps);
		game_buttons_control_down2(fps);
		game_buttons_control_down3(fps);
		game_buttons_control_down4(fps);
	}
}

void	game_buttons_control_down1(t_game *fps)
{
	if (fps->eng->event.key.keysym.sym == SDLK_1)
		switch_weapon(fps->eng, &fps->player, 0);
	if (fps->eng->event.key.keysym.sym == SDLK_2)
		switch_weapon(fps->eng, &fps->player, 1);
	if (fps->eng->event.key.keysym.sym == SDLK_o)
		change_floor(fps->eng, fps->player.cursector, 10);
	if (fps->eng->event.key.keysym.sym == SDLK_l)
		change_floor(fps->eng, fps->player.cursector, -10);
	if (fps->eng->event.key.keysym.sym == SDLK_u)
		change_ceil(fps->eng, fps->player.cursector, 10);
	if (fps->eng->event.key.keysym.sym == SDLK_j)
		change_ceil(fps->eng, fps->player.cursector, -10);
	if (fps->eng->event.key.keysym.sym == SDLK_LSHIFT)
		fps->player.controller.running = 3;
}

void	game_buttons_control_down2(t_game *fps)
{
	if (fps->eng->event.key.keysym.sym == SDLK_w)
		fps->player.controller.wasd[0] = 1;
	if (fps->eng->event.key.keysym.sym == SDLK_s)
		fps->player.controller.wasd[3] = 1;
	if (fps->eng->event.key.keysym.sym == SDLK_a)
		fps->player.controller.wasd[2] = 1;
	if (fps->eng->event.key.keysym.sym == SDLK_c &&
	fps->eng->grav == true)
	{
		if (fps->player.controller.ducking == 1)
		{
			fps->logic.duck_shift = 50;
			fps->player.controller.running -= 1;
			fps->player.controller.ducking = -1;
			fps->player.controller.falling = 1;
		}
		else if (fps->player.controller.ducking == -1)
		{
			fps->logic.duck_shift = 0;
			fps->player.controller.running += 1;
			fps->player.controller.ducking = 1;
			fps->player.position.z += 50;
		}
	}
}

void	game_buttons_control_down3(t_game *fps)
{
	if (fps->eng->event.key.keysym.sym == SDLK_SPACE
	&& fps->player.controller.falling != 1 && fps->eng->grav == true)
	{
		if (fps->player.controller.ducking == -1)
		{
			fps->player.controller.running += 1;
			fps->logic.duck_shift = 0;
			fps->player.position.z = fps->eng->world->sectors_array
			[fps->player.cursector].floor + 100 - fps->logic.duck_shift;
			fps->player.controller.ducking = 1;
		}
		else
		{
			fps->player.controller.falling = 1;
			if ((fps->player.position.z + 150) >=
			fps->eng->world->sectors_array[fps->player.cursector].ceil)
			{
				fps->player.position.z += fps->eng->world->sectors_array
				[fps->player.cursector].ceil - fps->player.position.z
				- HEAD_MARGIN;
			}
			else
				fps->player.position.z += 150;
		}
	}
}

void	game_buttons_control_down4(t_game *fps)
{
	if (fps->eng->event.key.keysym.sym == SDLK_d)
		fps->player.controller.wasd[1] = 1;
	if (fps->eng->event.key.keysym.sym == SDLK_e)
		use(fps->eng, &fps->player);
	if (fps->eng->event.key.keysym.sym == SDLK_z &&
	fps->eng->grav == false)
	{
		if (fps->player.position.z - 30 >
		fps->eng->world->sectors_array[fps->player.cursector].floor + 150)
			fps->player.position.z -= 30;
		else
			fps->player.position.z =
			fps->eng->world->sectors_array[fps->player.cursector].floor + 150;
	}
	if (fps->eng->event.key.keysym.sym == SDLK_SPACE &&
	fps->eng->grav == false)
	{
		if (fps->player.position.z + 30 <
		fps->eng->world->sectors_array[fps->player.cursector].ceil - 10)
			fps->player.position.z += 30;
		else
			fps->player.position.z =
			fps->eng->world->sectors_array[fps->player.cursector].ceil - 10;
	}
}
