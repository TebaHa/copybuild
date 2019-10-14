/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:36:15 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/15 00:01:33 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

SDL_Surface		*create_text(t_engine *eng, char *str, int color)
{
	SDL_Color	sdl_color;

	sdl_color = (SDL_Color) {(Uint8)color,
	(Uint8)(color >> 8), (Uint8)(color >> 16)};
	return (TTF_RenderText_Solid(eng->font, str, sdl_color));
}