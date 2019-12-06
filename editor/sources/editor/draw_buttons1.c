/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buttons1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 08:24:16 by eharrag-          #+#    #+#             */
/*   Updated: 2019/10/21 13:03:42 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	plasma_gun_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_PLASMA_GUN_X1;
	button->y = BUTTON_PLASMA_GUN_Y1;
	button->w = BUTTON_PLASMA_GUN_X2 - BUTTON_PLASMA_GUN_X1;
	button->h = BUTTON_PLASMA_GUN_Y2 - BUTTON_PLASMA_GUN_Y1;
	if (sdl->button_pushed == PLASMA_GUN_PUSH)
		draw_button(sdl, *button, " SET PLASMA GUN", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET PLASMA GUN", COLOR_UNPUSHED);
}

void	plasma_ammo_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_PLASMA_AMMO_X1;
	button->y = BUTTON_PLASMA_AMMO_Y1;
	button->w = BUTTON_PLASMA_AMMO_X2 - BUTTON_PLASMA_AMMO_X1;
	button->h = BUTTON_PLASMA_AMMO_Y2 - BUTTON_PLASMA_AMMO_Y1;
	if (sdl->button_pushed == PLASMA_AMMO_PUSH)
		draw_button(sdl, *button, " SET PLASMA AMMO", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET PLASMA AMMO", COLOR_UNPUSHED);
}

void	barrel_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_BARREL_X1;
	button->y = BUTTON_BARREL_Y1;
	button->w = BUTTON_BARREL_X2 - BUTTON_BARREL_X1;
	button->h = BUTTON_BARREL_Y2 - BUTTON_BARREL_Y1;
	if (sdl->button_pushed == BARREL_PUSH)
		draw_button(sdl, *button, " SET BARREL", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET BARREL", COLOR_UNPUSHED);
}

void	afrit_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_AFRIT_X1;
	button->y = BUTTON_AFRIT_Y1;
	button->w = BUTTON_AFRIT_X2 - BUTTON_AFRIT_X1;
	button->h = BUTTON_AFRIT_Y2 - BUTTON_AFRIT_Y1;
	if (sdl->button_pushed == AFRIT_PUSH)
		draw_button(sdl, *button, " SET AFRIT", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET AFRIT", COLOR_UNPUSHED);
}

void	cacodemon_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_CACODEMON_X1;
	button->y = BUTTON_CACODEMON_Y1;
	button->w = BUTTON_CACODEMON_X2 - BUTTON_CACODEMON_X1;
	button->h = BUTTON_CACODEMON_Y2 - BUTTON_CACODEMON_Y1;
	if (sdl->button_pushed == CACODEMON_PUSH)
		draw_button(sdl, *button, " SET CACODEMON", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET CACODEMON", COLOR_UNPUSHED);
}
