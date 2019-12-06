/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigloop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:26:54 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:56:38 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	clicks2(t_sdl *sdl)
{
	SDL_GetMouseState(&sdl->mouse_position.x, &sdl->mouse_position.y);
	if ((sdl->mouse_position.x > BUTTON_ARMOR_X1 &&
			sdl->mouse_position.x < BUTTON_ARMOR_X2) &&
			(sdl->mouse_position.y > BUTTON_ARMOR_Y1 &&
			sdl->mouse_position.y < BUTTON_ARMOR_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = ARMOR_PUSH;
	}
	else if ((sdl->mouse_position.x > BUTTON_POWER_UP_X1 &&
			sdl->mouse_position.x < BUTTON_POWER_UP_X2) &&
			(sdl->mouse_position.y > BUTTON_POWER_UP_Y1 &&
			sdl->mouse_position.y < BUTTON_POWER_UP_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = POWER_UP_PUSH;
	}
	else
		clicks3(sdl);
}

void	clicks1(t_sdl *sdl)
{
	SDL_GetMouseState(&sdl->mouse_position.x, &sdl->mouse_position.y);
	if ((sdl->mouse_position.x > BUTTON_PLAYER_X1 &&
			sdl->mouse_position.x < BUTTON_PLAYER_X2) &&
			(sdl->mouse_position.y > BUTTON_PLAYER_Y1 &&
			sdl->mouse_position.y < BUTTON_PLAYER_Y2))
	{
		sdl->type_pressed = PLAYER_TYPE;
		sdl->button_pushed = PLAYER_PUSH;
	}
	else if ((sdl->mouse_position.x > BUTTON_MEDKIT_X1 &&
			sdl->mouse_position.x < BUTTON_MEDKIT_X2) &&
			(sdl->mouse_position.y > BUTTON_MEDKIT_Y1 &&
			sdl->mouse_position.y < BUTTON_MEDKIT_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = MEDKIT_PUSH;
	}
	else
		clicks2(sdl);
}

void	clicks0(t_sdl *sdl)
{
	if (sdl->button_pushed == WALL_PUSH)
		make_wall(sdl);
	SDL_GetMouseState(&sdl->mouse_position.x, &sdl->mouse_position.y);
	if ((sdl->mouse_position.x > BUTTON_WALL_X1 &&
			sdl->mouse_position.x < BUTTON_WALL_X2) &&
			(sdl->mouse_position.y > BUTTON_WALL_Y1 &&
			sdl->mouse_position.y < BUTTON_WALL_Y2))
	{
		sdl->type_pressed = WALL_TYPE;
		sdl->button_pushed = WALL_PUSH;
	}
	else
		clicks1(sdl);
	if (sdl->type_pressed == PLAYER_TYPE || sdl->type_pressed == SPRITE_TYPE)
		make_player_or_sprite(sdl);
}

void	main_events(t_sdl *sdl)
{
	text_events(sdl);
	if (bigscarycondition(sdl) == 1)
		save_click(sdl);
	else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_BACKSPACE ==
			sdl->window_event.key.keysym.sym && sdl->is_input == 0)
		delete_last_command(sdl);
	else if (sdl->window_event.type == SDL_KEYDOWN && SDLK_DELETE ==
			sdl->window_event.key.keysym.sym)
		reset(sdl);
	else if (sdl->window_event.type == SDL_MOUSEBUTTONDOWN &&
			sdl->window_event.button.button == SDL_BUTTON_LEFT)
	{
		sdl->is_input = 0;
		clicks0(sdl);
	}
	draw(sdl);
}

void	big_loop(t_sdl *sdl)
{
	while (1)
	{
		if (SDL_PollEvent(&sdl->window_event))
		{
			exit_events(sdl);
			if (sdl->window_event.type == SDL_KEYDOWN && SDLK_ESCAPE ==
			sdl->window_event.key.keysym.sym)
				break ;
			if (sdl->save_click == 0)
				main_events(sdl);
		}
	}
}
