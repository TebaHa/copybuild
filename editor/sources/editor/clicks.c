/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clicks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 09:30:55 by eharrag-          #+#    #+#             */
/*   Updated: 2019/11/27 12:47:32 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	clicks6(t_sdl *sdl)
{
	SDL_GetMouseState(&sdl->mouse_position.x, &sdl->mouse_position.y);
	if ((sdl->mouse_position.x > BUTTON_IMP_X1 &&
			sdl->mouse_position.x < BUTTON_IMP_X2) &&
			(sdl->mouse_position.y > BUTTON_IMP_Y1 &&
			sdl->mouse_position.y < BUTTON_IMP_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = IMP_PUSH;
	}
	else if ((sdl->mouse_position.x > BUTTON_JETPACK_X1 &&
			sdl->mouse_position.x < BUTTON_JETPACK_X2) &&
			(sdl->mouse_position.y > BUTTON_JETPACK_Y1 &&
			sdl->mouse_position.y < BUTTON_JETPACK_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = JETPACK_PUSH;
	}
	else
		input_field_click(sdl);
}

void	clicks5(t_sdl *sdl)
{
	SDL_GetMouseState(&sdl->mouse_position.x, &sdl->mouse_position.y);
	if ((sdl->mouse_position.x > BUTTON_AFRIT_X1 &&
			sdl->mouse_position.x < BUTTON_AFRIT_X2) &&
			(sdl->mouse_position.y > BUTTON_AFRIT_Y1 &&
			sdl->mouse_position.y < BUTTON_AFRIT_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = AFRIT_PUSH;
	}
	else if ((sdl->mouse_position.x > BUTTON_CACODEMON_X1 &&
			sdl->mouse_position.x < BUTTON_CACODEMON_X2) &&
			(sdl->mouse_position.y > BUTTON_CACODEMON_Y1 &&
			sdl->mouse_position.y < BUTTON_CACODEMON_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = CACODEMON_PUSH;
	}
	else
		clicks6(sdl);
}

void	clicks4(t_sdl *sdl)
{
	SDL_GetMouseState(&sdl->mouse_position.x, &sdl->mouse_position.y);
	if ((sdl->mouse_position.x > BUTTON_PLASMA_AMMO_X1 &&
			sdl->mouse_position.x < BUTTON_PLASMA_AMMO_X2) &&
			(sdl->mouse_position.y > BUTTON_PLASMA_AMMO_Y1 &&
			sdl->mouse_position.y < BUTTON_PLASMA_AMMO_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = PLASMA_AMMO_PUSH;
	}
	else if ((sdl->mouse_position.x > BUTTON_BARREL_X1 &&
			sdl->mouse_position.x < BUTTON_BARREL_X2) &&
			(sdl->mouse_position.y > BUTTON_BARREL_Y1 &&
			sdl->mouse_position.y < BUTTON_BARREL_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = BARREL_PUSH;
	}
	else
		clicks5(sdl);
}

void	clicks3(t_sdl *sdl)
{
	SDL_GetMouseState(&sdl->mouse_position.x, &sdl->mouse_position.y);
	if ((sdl->mouse_position.x > BUTTON_RIFLE_AMMO_X1 &&
			sdl->mouse_position.x < BUTTON_RIFLE_AMMO_X2) &&
			(sdl->mouse_position.y > BUTTON_RIFLE_AMMO_Y1 &&
			sdl->mouse_position.y < BUTTON_RIFLE_AMMO_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = RIFLE_AMMO_PUSH;
	}
	else if ((sdl->mouse_position.x > BUTTON_PLASMA_GUN_X1 &&
			sdl->mouse_position.x < BUTTON_PLASMA_GUN_X2) &&
			(sdl->mouse_position.y > BUTTON_PLASMA_GUN_Y1 &&
			sdl->mouse_position.y < BUTTON_PLASMA_GUN_Y2))
	{
		sdl->type_pressed = SPRITE_TYPE;
		sdl->button_pushed = PLASMA_GUN_PUSH;
	}
	else
		clicks4(sdl);
}
