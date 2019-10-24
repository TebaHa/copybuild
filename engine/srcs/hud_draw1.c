/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 23:13:48 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/24 11:53:37 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		draw_from_s_to_s_help_1(t_surf_data *data, SDL_Surface *src)
{
	data->alpha = ((unsigned char *)src->pixels)
	[(data->y * 4 * src->w + data->x * 4) + 3];
	if (data->alpha == 255)
		draw_from_s_to_s_help(data, src);
	data->ty++;
	data->y++;
}

void		draw_from_s_to_s_help(t_surf_data *data, SDL_Surface *src)
{
	data->red = ((unsigned char *)src->pixels)
	[(data->y * 4 * src->w + data->x * 4)];
	data->green = ((unsigned char *)src->pixels)
	[(data->y * 4 * src->w + data->x * 4) + 1];
	data->blue = ((unsigned char *)src->pixels)
	[(data->y * 4 * src->w + data->x * 4) + 2];
	data->pix[data->ty * WIDTH + data->tx] =
	get_rgb(data->red, data->green, data->blue, data->alpha);
}
