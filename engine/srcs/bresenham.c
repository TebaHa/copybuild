/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 00:12:42 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/08 16:01:13 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	ft_swap(float *a, float *b)
{
	float tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

void		triangle_lines(t_polygone *t, t_engine *eng)
{
	if (t->vertices_array[0].y == t->vertices_array[1].y
	&& t->vertices_array[0].y == t->vertices_array[2].y)
		return ;
	bresenham_line(&(t->vertices_array[0]), &(t->vertices_array[1]), eng, get_rgb(((t->color) >> 16), ((t->color) >> 8), ((t->color)), 255));
	bresenham_line(&(t->vertices_array[1]), &(t->vertices_array[2]), eng, get_rgb(((t->color) >> 16), ((t->color) >> 8), ((t->color)), 255));
	bresenham_line(&(t->vertices_array[2]), &(t->vertices_array[0]), eng, get_rgb(((t->color) >> 16), ((t->color) >> 8), ((t->color)), 255));
}

void		swapper(t_point_3d *a, t_point_3d *b, int *steep)
{
	*steep = 0;
	if (fabsf(a->x - b->x) < fabsf(a->y - b->y))
	{
		ft_swap(&(a->x), &(a->y));
		ft_swap(&(b->x), &(b->y));
		*steep = 1;
	}
	if (a->x > b->x)
	{
		ft_swap(&(a->x), &(b->x));
		ft_swap(&(a->y), &(b->y));
	}
}

t_bcontex	bresenham_init(t_point_3d *beg, t_point_3d *end)
{
	t_bcontex	c;

	c.b.x = beg->x;
	c.b.y = beg->y;
	c.e.x = end->x;
	c.e.y = end->y;
	swapper(&c.b, &c.e, &c.steep);
	c.dx = c.e.x - c.b.x;
	c.dy = c.e.y - c.b.y;
	c.derror2 = fabs(c.dy) * 2;
	c.error2 = 0;
	c.y = c.b.y;
	c.x = c.b.x;
	return (c);
}

void		bresenham_put_pixel(t_bcontex *c,
								t_engine *eng, int color, int zmax)
{
	if (((c->steep && ((c->x >= 0 && c->x < HEIGHT)
	&& (c->y >= 0 && c->y < WIDTH) &&
	(eng->z_buff[c->y + c->x * WIDTH] < zmax + 1)))
	|| (!c->steep && ((c->y >= 0 && c->y < HEIGHT)
	&& (c->x >= 0 && c->x < WIDTH))
	&& (eng->z_buff[c->x + c->y * WIDTH] < zmax + 1))))
	{
		sdl_put_pixel(eng->surface, c->steep ? c->y : c->x,
		c->steep ? c->x : c->y, color);
	}
}

void		bresenham_line(t_point_3d *beg, t_point_3d *end,
							t_engine *eng, int color)
{
	t_bcontex	c;

	c = bresenham_init(beg, end);
	while (c.x <= c.e.x)
	{
		bresenham_put_pixel(&c, eng, color, fmaxf(beg->z, end->z));
		c.error2 += c.derror2;
		if (c.error2 > c.dx)
		{
			c.y += c.e.y > c.b.y ? 1 : -1;
			c.error2 -= c.dx * 2;
		}
		c.x++;
	}
}
