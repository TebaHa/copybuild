/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:55:56 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/06 22:25:48 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	draw_player(t_image *image, int x, int y, int angle)
{
	int	x0;
	int y0;

	x0 = x - 1;
	while (x0 <= x + 1)
	{
		y0 = y - 1;
		while (y0 <= y + 1)
		{
			put_on_image(x0, y0, 0xFF0000, image);
			y0++;
		}
		x0++;
	}
	draw_line(image, (t_point){x, y}, (t_point){(int)(cos(angle) * 20 + x), (int)(sin(angle) * 20 + y)}, 0x2F4F4F);
}

void	draw_map(t_image *image, t_portals *lvl)
{
	int	i;
	int	color;

	i = 0;
	while (i < lvl->wall_count)
	{
		printf("%lu\n", lvl->wall_array[i].id);
		if (lvl->wall_array[i].next_sector != -1)
			color = 0xFFFFFF;
		else
			color = 0xFFFFFF;
		draw_line(image, lvl->wall_array[i].pos.a, lvl->wall_array[i].pos.b, color);
		i++;
	}
}

void	draw_line(t_image *image, t_point a, t_point b, int color)
{
	int	dx;
	int	dy;
	int	p;
	int	x;
	int	y;

	dx = b.x - a.x;
	dy = b.y - a.y;
	x = a.x;
	y = a.y;
	p = 2 * dy - dx;
	while(x < b.x)
	{
		if(p >= 0)
		{
			put_on_image(x, y, color, image);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			put_on_image(x, y, color, image);
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}

void	put_on_image(int x, int y, int color, t_image *image)
{
	size_t	offset;
	int		*ptr;

	ptr = (int *)image->ptr_data;
	offset = x + image->width * y;
	ptr[offset] = color;
}
