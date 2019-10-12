/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:36:15 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/12 11:23:05 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

SDL_Surface		*create_text(t_engine *eng, char *str, int color)
{
	SDL_Color	sdl_color;
	SDL_Surface	*res;

	sdl_color = (SDL_Color) {(Uint8)color, (Uint8)(color >> 8), (Uint8)(color >> 16)};
	res = TTF_RenderText_Solid(eng->font, "Welcome to Gigi Labs", sdl_color);
}