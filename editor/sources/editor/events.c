/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:58:34 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:56:13 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	textinput(t_sdl *sdl)
{
	if (sdl->map_name->text_size + 1 < sdl->map_name->max_text_size)
	{
		ft_strcat(sdl->map_name->text, sdl->window_event.text.text);
		sdl->map_name->text_size++;
	}
}

void	text_events(t_sdl *sdl)
{
	if (sdl->window_event.type == SDL_KEYDOWN &&
			sdl->is_input == 1 && SDLK_BACKSPACE ==
			sdl->window_event.key.keysym.sym)
		delete_one_symbol(sdl);
	else if (sdl->window_event.type == SDL_TEXTINPUT && sdl->is_input == 1)
		textinput(sdl);
}

void	exit_events(t_sdl *sdl)
{
	if (SDL_QUIT == sdl->window_event.type)
		exit(0);
}
