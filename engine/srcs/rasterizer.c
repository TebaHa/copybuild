/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:24:28 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/04 00:40:29 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

/*
void			engine_do_calc(t_tric *trg)
{
	trg->second_half = trg->i > trg->t1.y - trg->t0.y || trg->t1.y == trg->t0.y;
	trg->segment_height = trg->second_half
	? trg->t2.y - trg->t1.y : trg->t1.y - trg->t0.y;
	trg->alpha = (double)trg->i / trg->total_height;
	trg->beta = (double)(trg->i - (trg->second_half
	? trg->t1.y - trg->t0.y : 0)) / trg->segment_height;
	trg->a.x = trg->t0.x + (trg->t2.x - trg->t0.x) * trg->alpha;
	trg->a.y = trg->t0.y + (trg->t2.y - trg->t0.y) * trg->alpha;
	trg->b.x = trg->second_half ? trg->t1.x + (trg->t2.x - trg->t1.x)
	* trg->beta : trg->t0.x + (trg->t1.x - trg->t0.x) * trg->beta;
	trg->b.y = trg->second_half ? trg->t1.y + (trg->t2.y - trg->t1.y)
	* trg->beta : trg->t0.y + (trg->t1.y - trg->t0.y) * trg->beta;
	if (trg->a.x > trg->b.x)
		point_swap(&trg->a, &trg->b);
	trg->j = trg->a.x;
}

void			engine_do_draw(t_engine *eng, t_player *plr, t_tric *trg, int color)
{
	trg->phi = trg->b.x == trg->a.x ? 1.0 :
	(double)(trg->j - trg->a.x) / (double)(trg->b.x - trg->a.x);
	trg->p.x = trg->a.x + (trg->b.x - trg->a.x) * trg->phi;
	trg->p.y = trg->a.y + (trg->b.y - trg->a.y) * trg->phi;
	if (((trg->p.x >= 0 && trg->p.x < WIDTH)
	&& (trg->p.y >= 0 && trg->p.y < HEIGHT)))
	{
		color = get_rgb(((color) >> 16), ((color) >> 8), ((color)), 255);
		sdl_put_pixel(eng->surface, trg->p.x, trg->p.y, color);
	}
}

int				engine_init_triangle(t_polygone *t, t_tric *trg)
{
	trg->t0 = (t_point_3d){t->vertices_array[0].x, t->vertices_array[0].y, t->vertices_array[0].z};
	trg->t1 = (t_point_3d){t->vertices_array[1].x, t->vertices_array[1].y, t->vertices_array[1].z};
	trg->t2 = (t_point_3d){t->vertices_array[2].x, t->vertices_array[2].y, t->vertices_array[2].z};
	if (trg->t0.y == trg->t1.y && trg->t0.y == trg->t2.y)
		return (0);
	if (trg->t0.y > trg->t1.y)
		point_swap(&(trg->t0), &(trg->t1));
	if (trg->t0.y > trg->t2.y)
		point_swap(&(trg->t0), &(trg->t2));
	if (trg->t1.y > trg->t2.y)
		point_swap(&(trg->t1), &(trg->t2));
	trg->total_height = (trg->t2.y) - (trg->t0.y);
	trg->i = 0;
	return (1);
}

void			engine_triangle(t_engine *eng, t_player *plr, t_polygone *t)
{
	t_tric		trg;
	int			f;

	f = engine_init_triangle(t, &trg);
	if (f == 0)
		return ;
	while (trg.i < trg.total_height)
	{
		engine_do_calc(&trg);
		while (trg.j <= trg.b.x)
		{
			engine_do_draw(eng, plr, &trg, t->color);
			trg.j++;
		}
		trg.i++;
	}
}
 */

float			edge_function(t_point_3d *a, t_point_3d *b, t_point_3d *c)
{
	 return ((c->x - a->x) * (b->y - a->y) - (c->y - a->y) * (b->x - a->x));
}

void			engine_rasterize_triangle(t_engine *eng, t_player *plr, t_polygone *t)
{
	t_point_3d a = t->vertices_array[0];
	t_point_3d b = t->vertices_array[1];
	t_point_3d c = t->vertices_array[2];

	float xmin = min(a.x,min(b.x, c.x));
	float ymin = min(a.y,min(b.y, c.y));
	float xmax = max(a.x,max(b.x, c.x));
	float ymax = max(a.y,max(b.y, c.y));

	if (xmin > WIDTH - 1 || xmax < 0 || ymin > HEIGHT - 1 || ymax < 0)
		return ;

	uint32_t x0 = max((int32_t)(0),(int32_t)(floor(xmin)));
	uint32_t x1 = min(((int32_t)(WIDTH) - 1),(int32_t)(floor(xmax)));
	uint32_t y0 = max((int32_t)(0), (int32_t)(floor(ymin)));
	uint32_t y1 = min(((int32_t)(HEIGHT) - 1),(int32_t)(floor(ymax)));

	float area = edge_function(&a, &b, &c);

	for (uint32_t y = y0; y <= y1; ++y)
	{
		for (uint32_t x = x0; x <= x1; ++x)
		{
			t_point_3d pixelSample = (t_point_3d){x + 0.5, y + 0.5, 0};
			float w0 = edge_function(&b, &c, &pixelSample);
			float w1 = edge_function(&c, &a, &pixelSample);
			float w2 = edge_function(&a, &b, &pixelSample);
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 /= area;
				w1 /= area;
				w2 /= area;
				float oneOverZ = a.z * w0 + b.z * w1 + c.z * w2;
				float z = 1 / oneOverZ;
				if (z < eng->z_buff[y * WIDTH + x])
				{
					eng->z_buff[y * WIDTH + x] = z;
					t_point_2d st = {a.x * w0 + b.x * w1 + c.x * w2, a.y * w0 + b.y * w1 + c.y * w2};
					st.x *= z, st.y *= z;
					sdl_put_pixel(eng->surface, x, y, t->color);
				}
			}
		}
	}
}
