/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:05:42 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 15:15:05 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	choose_the_status2(t_sdl *sdl, SDL_Rect *button)
{
	SDL_Color *color_text;

	color_text = NULL;
	if (sdl->status_code == CODE_OVERLAY_OR_DOUBLEPORT &&
		sdl->is_overlay == 1)
	{
		color_text = create_sdl_color(255, 0, 0, 255);
		draw_text(sdl, "Got a match of sectors", *button, *color_text);
	}
	else if (sdl->status_code == CODE_OVERLAY_OR_DOUBLEPORT &&
			sdl->is_doubleport == 1)
	{
		color_text = create_sdl_color(255, 0, 0, 255);
		draw_text(sdl, "Double portal is not allowed", *button, *color_text);
	}
	free(color_text);
}

void	choose_the_status(t_sdl *sdl, SDL_Rect *button)
{
	SDL_Color *color_text;

	color_text = NULL;
	if (sdl->status_code == CODE_ALREADY_EXIST)
	{
		sdl->save_click = 0;
		color_text = create_sdl_color(255, 0, 0, 255);
		draw_text(sdl, "File already exist", *button, *color_text);
	}
	else if (sdl->status_code == CODE_OK)
	{
		color_text = create_sdl_color(0, 255, 0, 255);
		draw_text(sdl, "Save complete", *button, *color_text);
	}
	else if (sdl->status_code == CODE_NO_FILENAME)
	{
		color_text = create_sdl_color(255, 0, 0, 255);
		draw_text(sdl, "Empty filename", *button, *color_text);
	}
	else if (sdl->status_code == CODE_NO_PLAYER)
	{
		color_text = create_sdl_color(255, 0, 0, 255);
		draw_text(sdl, "No player on the map", *button, *color_text);
	}
	free(color_text);
}

void	status_text(t_sdl *sdl, SDL_Rect *button)
{
	button = create_rect(BUTTON_STATUS_X1, BUTTON_STATUS_Y1,
			BUTTON_STATUS_X2 - BUTTON_STATUS_X1,
			BUTTON_STATUS_Y2 - BUTTON_STATUS_Y1);
	choose_the_status(sdl, button);
	choose_the_status2(sdl, button);
	free(button);
}
