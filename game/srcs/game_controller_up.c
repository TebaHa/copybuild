/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controller_up.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:42:24 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/18 22:14:57 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	game_buttons_control_up_main(t_game *fps)
{
	if (fps->eng->event.button.type == SDL_MOUSEBUTTONDOWN)
		if (fps->eng->event.button.button == SDL_BUTTON_LEFT)
			fire(&fps->player, 1);
	if (fps->eng->event.button.type == SDL_MOUSEBUTTONUP)
		if (fps->eng->event.button.button == SDL_BUTTON_LEFT)
			fire(&fps->player, 0);
	if (fps->eng->event.type == SDL_KEYUP)
	{
		if (fps->eng->event.key.keysym.sym == SDLK_LSHIFT)
			fps->player.controller.running = 4;
		if (fps->eng->event.key.keysym.sym == SDLK_w)
			fps->player.controller.wasd[0] = 0;
		if (fps->eng->event.key.keysym.sym == SDLK_s)
			fps->player.controller.wasd[3] = 0;
		if (fps->eng->event.key.keysym.sym == SDLK_a)
			fps->player.controller.wasd[2] = 0;
		if (fps->eng->event.key.keysym.sym == SDLK_d)
			fps->player.controller.wasd[1] = 0;
	}
}
