/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buttons2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 08:37:22 by eharrag-          #+#    #+#             */
/*   Updated: 2019/11/27 10:17:01 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	imp_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_IMP_X1;
	button->y = BUTTON_IMP_Y1;
	button->w = BUTTON_IMP_X2 - BUTTON_IMP_X1;
	button->h = BUTTON_IMP_Y2 - BUTTON_IMP_Y1;
	if (sdl->button_pushed == IMP_PUSH)
		draw_button(sdl, *button, " SET IMP", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET IMP", COLOR_UNPUSHED);
}

void	jetpack_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_JETPACK_X1;
	button->y = BUTTON_JETPACK_Y1;
	button->w = BUTTON_JETPACK_X2 - BUTTON_JETPACK_X1;
	button->h = BUTTON_JETPACK_Y2 - BUTTON_JETPACK_Y1;
	if (sdl->button_pushed == JETPACK_PUSH)
		draw_button(sdl, *button, " SET JETPACK", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " SET JETPACK", COLOR_UNPUSHED);
}

void	wall_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_WALL_X1;
	button->y = BUTTON_WALL_Y1;
	button->w = BUTTON_WALL_X2 - BUTTON_WALL_X1;
	button->h = BUTTON_WALL_Y2 - BUTTON_WALL_Y1;
	if (sdl->button_pushed == WALL_PUSH)
		draw_button(sdl, *button, " WALL", COLOR_PUSHED);
	else
		draw_button(sdl, *button, " WALL", COLOR_UNPUSHED);
}

void	save_button(t_sdl *sdl, SDL_Rect *button)
{
	button->x = BUTTON_SAVE_X1;
	button->y = BUTTON_SAVE_Y1;
	button->w = BUTTON_SAVE_X2 - BUTTON_SAVE_X1;
	button->h = BUTTON_SAVE_Y2 - BUTTON_SAVE_Y1;
	draw_button(sdl, *button, " SAVE THE MAP", SAVE_BUTTON);
}
