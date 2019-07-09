/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:42:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/09 21:59:12 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_vec4		matrix_on_vec_multiply(t_mat4 a, t_vec4 b)
{
	t_vec4	res;

	res.x = a.values[0][0] * b.x + a.values[0][1] * b.y
	+ a.values[0][2] * b.z + a.values[0][3] * b.w;
	res.y = a.values[1][0] * b.x + a.values[1][1] * b.y
	+ a.values[1][2] * b.z + a.values[1][3] * b.w;
	res.z = a.values[2][0] * b.x + a.values[2][1] * b.y
	+ a.values[2][2] * b.z + a.values[2][3] * b.w;
	res.w = a.values[3][0] * b.x + a.values[3][1] * b.y
	+ a.values[3][2] * b.z + a.values[3][3] * b.w;
	return (res);
}

t_mat4		getzeroaffinmat4(void)
{
	t_mat4	res;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			res.values[i][j] = 0;
	}
	res.values[0][0] = 1;
	res.values[1][1] = 1;
	res.values[2][2] = 1;
	res.values[3][3] = 1;
	return (res);
}

t_point_3d	engine_count_perspective(t_point_3d a, int c)
{
	t_vec4	res;
	t_mat4	mt4;

	mt4 = getzeroaffinmat4();
	mt4.values[3][2] -= (float)(1.0 / (float)c);
	res = matrix_on_vec_multiply(mt4,
	(t_vec4){(float)a.x, (float)a.y, (float)a.z, 1.0});
	a.x = res.x / res.w;
	a.y = res.y / res.w;
	a.z = res.z / res.w;
	return (a);
}

void		engine_render_sector(t_engine *eng, t_sector *sec, t_player *plr)
{
	int			i;

	i = 0;
	plr->position = plr->position;
	while (i < sec->objects_size)
	{
		engine_render_obj(eng, sec->objects_array[i], -50);
		i++;
	}
}

void		engine_render_obj(t_engine *eng, t_object obj, int view)
{
	int			i;
	t_point_3d	a;
	t_point_3d	b;
	t_point_2d	ta;
	t_point_2d	tb;

	i = 0;
	a = engine_count_perspective(obj.polies_array->vertices[0], view);
	b = engine_count_perspective(obj.polies_array->vertices[3], view);
	ta = (t_point_2d){a.x, a.y};
	tb = (t_point_2d){b.x, b.y};
	engine_draw_line(eng, ta, tb, 0xFF0000);
	while (i < obj.polies_array->vertices_size - 1)
	{
		a = engine_count_perspective(obj.polies_array->vertices[i], view);
		b = engine_count_perspective(obj.polies_array->vertices[i + 1], view);
		ta = (t_point_2d){a.x, a.y};
		tb = (t_point_2d){b.x, b.y};
		engine_draw_line(eng, ta, tb, 0xFF0000);
		i++;
	}
}

void		engine_draw_line(t_engine *eng, t_point_2d a, t_point_2d b, int color)
{
	float			len;
	float			deltax;
	float			deltay;
	unsigned long	x;
	unsigned long	y;
	int				i;

	len = (fabs(b.x - a.x) > fabs(b.y - a.y)) ? fabs(b.x - a.x) : fabs(b.y - a.y);
	deltax = (b.x - a.x) / len;
	deltay = (b.y - a.y) / len;
	i = 0;
	while (i < (int)len)
	{
		a.x += deltax;
		a.y += deltay;
		x = (int)(a.x);
		y = (int)(a.y);
		if ((a.x + WIDTH / 2) < WIDTH && (a.y + HEIGHT / 2) < HEIGHT)
			sdl_put_pixel(eng->ren, (a.x + WIDTH / 2), (a.y + HEIGHT / 2), color);
		i++;
	}
}

void	engine_render_frame(t_engine *eng)
{
	SDL_RenderPresent(eng->ren);
}

void	sdl_clear_window(SDL_Renderer *ren)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderClear(ren);
}

void	sdl_put_pixel(SDL_Renderer *ren, int x, int y, int color)
{
	SDL_SetRenderDrawColor(ren, (Uint8)(color >> 16), (Uint8)(color >> 8), (Uint8)(color), 255);
	SDL_RenderDrawPoint(ren, x, y);
}
