/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 00:17:18 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/04 00:17:35 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

float		percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int			get_light(int start, int end, float percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			get_color(int current, int start,
										int end, int colors[2])
{
	int		red;
	int		green;
	int		blue;
	float	percentage;

	percentage = percent(start, end, current);
	red = get_light((colors[0] >> 16)
	& 0xFF, (colors[1] >> 16) & 0xFF, percentage);
	green = get_light((colors[0] >> 8)
	& 0xFF, (colors[1] >> 8) & 0xFF, percentage);
	blue = get_light(colors[0] & 0xFF, colors[1] & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
