/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_headline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:23:36 by eharrag-          #+#    #+#             */
/*   Updated: 2019/11/27 10:04:41 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_headline(t_sdl *sdl)
{
	SDL_Rect	headline;
	SDL_Rect	bottomline;
	SDL_Color	*color_text;

	headline.x = 94;
	headline.y = 25;
	headline.w = (int)SIZE_WIN_X * 0.8 - headline.x * 2;
	headline.h = 50;
	SDL_SetRenderDrawColor(sdl->renderer, 20, 20, 40, 0);
	color_text = create_sdl_color(204, 153, 255, 255);
	draw_text(sdl, " Remove last command - BACKSPACE",
		headline, *color_text);
	bottomline.x = 94;
	bottomline.y = SIZE_WIN_Y - headline.y - headline.h;
	bottomline.w = (int)SIZE_WIN_X * 0.8 - headline.x * 2;
	bottomline.h = headline.h;
	draw_text(sdl,
		" Full reset - DELETE                  Have fun!",
		bottomline, *color_text);
	free(color_text);
}
