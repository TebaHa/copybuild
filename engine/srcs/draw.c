/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:55:56 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/07 20:51:40 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	draw_map_3d(t_image *image, t_portals *lvl, t_player *plr)
{
	t_point	ta;
	t_point	tb;
	t_point	tz;
	t_point	tw;
	double	angle;

	angle = plr->angle * M_PI / 180.0;
	ta.x = lvl->wall_array[0].pos.a.x - plr->px;
	ta.y = lvl->wall_array[0].pos.a.y - plr->py;
	tb.x = lvl->wall_array[0].pos.b.x - plr->px;
	tb.y = lvl->wall_array[0].pos.b.y - plr->py;
	tz.x = ta.x * cos(angle) + ta.y * sin(angle);
	tz.y = tb.x * cos(angle) + tb.y * sin(angle);
	ta.x = ta.x * sin(angle) - ta.y * cos(angle);
	ta.y = tb.x * sin(angle) - tb.y * cos(angle);
	if (tz.x != 0)
	{
		ta.x = -ta.x * 16 / tz.x;
		tw.x = -50 / tz.x;
		tb.x = 50 / tz.x;
	}
	if (tz.y != 0)
	{
		ta.y = -ta.y * 16 / tz.y;
		tw.y = -50 / tz.y;
		tb.y = 50 / tz.y;
	}
	draw_line(image, (t_point){50 + ta.x, 50 + tw.x, 0}, (t_point){50 + ta.y, 50 + tw.y, 0}, 0x2F4F4F);
	draw_line(image, (t_point){50 + ta.x, 50 + tb.x, 0}, (t_point){50 + ta.y, 50 + tb.y, 0}, 0x2F4F4F);
	draw_line(image, (t_point){50 + ta.x, 50 + tw.x, 0}, (t_point){50 + ta.x, 50 + tb.x, 0}, 0xFF0000);
	draw_line(image, (t_point){50 + ta.y, 50 + tw.y, 0}, (t_point){50 + ta.y, 50 + tb.y, 0}, 0xFF0000);
}

void	draw_player_2d(t_image *image, int x, int y, double angle)
{
	int	x0;
	int y0;

	x0 = x - 1;
	angle = angle * M_PI / 180.0;
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
	draw_line(image, (t_point){x, y, 0}, (t_point){x, (y + 15), 0}, 0x2F4F4F);
}

void	draw_map_2d(t_image *image, t_portals *lvl, t_player *plr)
{
	int		i;
	int		color;
	t_point	ta;
	t_point	tb;
	t_point	tz;
	double	angle;

	i = 0;
	angle = plr->angle * M_PI / 180.0;
	while (i < lvl->wall_count)
	{
		if (lvl->wall_array[i].next_sector != -1)
			color = 0xFF0000;
		else
			color = 0xFFFFFF;
		ta.x = lvl->wall_array[i].pos.a.x - plr->px;
		ta.y = lvl->wall_array[i].pos.a.y - plr->py;
		tb.x = lvl->wall_array[i].pos.b.x - plr->px;
		tb.y = lvl->wall_array[i].pos.b.y - plr->py;
		tz.x = ta.x * cos(angle) + ta.y * sin(angle);
		tz.y = tb.x * cos(angle) + tb.y * sin(angle);
		ta.x = ta.x * sin(angle) - ta.y * cos(angle);
		ta.y = tb.x * sin(angle) - tb.y * cos(angle);
		draw_line(image, (t_point){ta.x, tz.x, 0}, (t_point){ta.y, tz.y, 0}, color);
		i++;
	}
}

void	draw_line(t_image *image, t_point a, t_point b, int color)
{
	int	dx;
	int	dy;
	int	err;
	int	sx;
	int	sy;
	int	e2;

	dx = abs(b.x - a.x);
	sx = a.x < b.x ? 1 : -1;
	dy = abs(b.y - a.y);
	sy = a.y < b.y ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		put_on_image(a.x + image->width, a.y, color, image);
		if (a.x == b.x && a.y == b.y)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			a.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			a.y += sy;
		}
	}
}

void	put_on_image(int x, int y, int color, t_image *image)
{
	size_t	offset;
	int		*ptr;

	ptr = (int *)image->ptr_data;
	offset = (x + image->width / 2) + image->width * (y + image->height / 2);
	if (offset <= (unsigned long)image->height * image->width)
		ptr[offset] = color;
}
