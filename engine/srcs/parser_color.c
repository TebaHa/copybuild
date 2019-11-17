/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 00:17:18 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/14 19:18:21 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		util_read_color(t_color *color, char *str)
{
	int		argb_color;

	argb_color = util_int16_data_filler(str);
	color->argb = argb_color;
	color->alpha = ((argb_color >> 20) & 0xFF);
	color->red = (float)1 / 0xFF * ((argb_color >> 16) & 0xFF);
	color->green = (float)1 / 0xFF * ((argb_color >> 8) & 0xFF);
	color->blue = (float)1 / 0xFF * (argb_color & 0xFF);
}
