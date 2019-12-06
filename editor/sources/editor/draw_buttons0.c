/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buttons0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 08:24:16 by eharrag-          #+#    #+#             */
/*   Updated: 2019/10/21 13:03:21 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	player_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_PLAYER_X1;
	button->y = BUTTON_PLAYER_Y1;
	button->w = BUTTON_PLAYER_X2 - BUTTON_PLAYER_X1;
	button->h = BUTTON_PLAYER_Y2 - BUTTON_PLAYER_Y1;
	if (sdl->button_pushed == PLAYER_PUSH)
		draw_button(sdl, *button, " PLAYER", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " PLAYER", COLOR_UNPUSHED);
}

void	medkit_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_MEDKIT_X1;
	button->y = BUTTON_MEDKIT_Y1;
	button->w = BUTTON_MEDKIT_X2 - BUTTON_MEDKIT_X1;
	button->h = BUTTON_MEDKIT_Y2 - BUTTON_MEDKIT_Y1;
	if (sdl->button_pushed == MEDKIT_PUSH)
		draw_button(sdl, *button, " SET A MEDKIT", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET A MEDKIT", COLOR_UNPUSHED);
}

void	armor_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_ARMOR_X1;
	button->y = BUTTON_ARMOR_Y1;
	button->w = BUTTON_ARMOR_X2 - BUTTON_ARMOR_X1;
	button->h = BUTTON_ARMOR_Y2 - BUTTON_ARMOR_Y1;
	if (sdl->button_pushed == ARMOR_PUSH)
		draw_button(sdl, *button, " SET AN ARMOR", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET AN ARMOR", COLOR_UNPUSHED);
}

void	power_up_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_POWER_UP_X1;
	button->y = BUTTON_POWER_UP_Y1;
	button->w = BUTTON_POWER_UP_X2 - BUTTON_POWER_UP_X1;
	button->h = BUTTON_POWER_UP_Y2 - BUTTON_POWER_UP_Y1;
	if (sdl->button_pushed == POWER_UP_PUSH)
		draw_button(sdl, *button, " SET POWER UP", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET POWER UP", COLOR_UNPUSHED);
}

void	rifle_ammo_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_RIFLE_AMMO_X1;
	button->y = BUTTON_RIFLE_AMMO_Y1;
	button->w = BUTTON_RIFLE_AMMO_X2 - BUTTON_RIFLE_AMMO_X1;
	button->h = BUTTON_RIFLE_AMMO_Y2 - BUTTON_RIFLE_AMMO_Y1;
	if (sdl->button_pushed == RIFLE_AMMO_PUSH)
		draw_button(sdl, *button, " SET RIFLE AMMO", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET RIFLE AMMO", COLOR_UNPUSHED);
}
