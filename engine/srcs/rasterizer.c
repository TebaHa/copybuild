/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:24:28 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/08 15:05:30 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

/*
void			engine_do_calc(t_tric *trg)
{
	trg->second_half = trg->i > trg->t1.y - trg->t0.y || trg->t1.y == trg->t0.y;
	trg->segment_height = trg->second_half
	? trg->t2.y - trg->t1.y : trg->t1.y - trg->t0.y;
	trg->alpha = (float)trg->i / trg->total_height;
	trg->beta = (float)(trg->i - (trg->second_half
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
	(float)(trg->j - trg->a.x) / (float)(trg->b.x - trg->a.x);
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
	if (trg->t1.x> trg->t2.x)
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
		}		trg.i++;
	}
}
*/
/*
float			edge_function(t_point_3d *a, t_point_3d *b, t_point_3d *c)
{
	 return ((c->x - a->x) * (b->y - a->y) - (c->y - a->y) * (b->x - a->x));
}

void			engine_rasterize_triangle(t_engine *eng, t_player *plr, t_polygone *t)
{
	t_point_3d a = t->vertices_array[0];
	t_point_3d b = t->vertices_array[1];
	t_point_3d c = t->vertices_array[2];

	if (a.y == b.y && a.y == c.y)
		return ;
	if (a.x >= b.x)
		point_swap(&(a), &(b));
	if (a.x >= c.x)
		point_swap(&(a), &(c));
	if (b.y >= c.y)
		point_swap(&(b), &(c));
	float xmin = min(a.x,min(b.x, c.x));
	float ymin = min(a.y,min(b.y, c.y));
	float xmax = max(a.x,max(b.x, c.x));
	float ymax = max(a.y,max(b.y, c.y));
	if (xmin > WIDTH - 1 || xmax < 0 || ymin > HEIGHT - 1 || ymax < 0)
		return ;
	uint32_t x0 = max((int32_t)(0),(int32_t)(floorf(xmin)));
	uint32_t x1 = min(((int32_t)((WIDTH) - 1)),(int32_t)(floorf(xmax)));
	uint32_t y0 = max((int32_t)(0), (int32_t)(floorf(ymin)));
	uint32_t y1 = min(((int32_t)((HEIGHT) - 1)),(int32_t)(floorf(ymax)));
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
				if (z > eng->z_buff[y * WIDTH + x])
				{
					eng->z_buff[y * WIDTH + x] = z;
					sdl_put_pixel(eng->surface, x, y, get_rgb(((t->color) >> 16), ((t->color) >> 8), ((t->color)), 255));
				}
			}
		}
	}
}
*/
t_point_3d	cross(t_point_3d a, t_point_3d b)
{
	t_point_3d res;

	res.x = (a.y * b.z) - (a.z * b.y);
	res.y = (a.z * b.x) - (a.x * b.z);
	res.z = (a.x * b.y) - (a.y * b.x);
	return (res);
}

t_point_3d	barycentric(t_fix_point_2d pts[3], t_fix_point_2d *p)
{
	t_point_3d u = cross((t_point_3d){0, pts[2].x - pts[0].x, pts[1].x - pts[0].x,
	pts[0].x - p->x}, (t_point_3d){0, pts[2].y - pts[0].y, pts[1].y - pts[0].y, pts[0].y - p->y});
	if (fabsf(u.z) > 1e-2)
		return ((t_point_3d){(int)0, (float)(1.f - (u.x + u.y) / u.z), (float)(u.y / u.z), (float)(u.x / u.z)});
	return ((t_point_3d){(int)0, (float)-1, (float)1, (float)1}); // triangle is degenerate, in this case return smth with negative coordinates
}

void			engine_triangle(t_engine *eng, t_player *plr, t_polygone *t)
{
	t_fix_point_2d	bboxmin;
	t_fix_point_2d	bboxmax;
	t_fix_point_2d	clampt;
	t_fix_point_2d	p;
	t_fix_point_2d	pts2[3];
	int 			color;

	pts2[0] = (t_fix_point_2d){t->vertices_array[0].x, t->vertices_array[0].y};
	pts2[1] = (t_fix_point_2d){t->vertices_array[1].x, t->vertices_array[1].y};
	pts2[2] = (t_fix_point_2d){t->vertices_array[2].x, t->vertices_array[2].y};
	bboxmin = (t_fix_point_2d){INT32_MAX, INT32_MAX};
	bboxmax = (t_fix_point_2d){INT32_MIN, INT32_MIN};
	clampt = (t_fix_point_2d){WIDTH - 1, HEIGHT - 1};
	color = get_rgb(((t->color) >> 16), ((t->color) >> 8), ((t->color)), 255);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			((int *)&bboxmin)[j] = max(0.f, min(((int *)&bboxmin)[j], ((int *)&pts2[i])[j]));
			((int *)&bboxmax)[j] = min(((int *)&clampt)[j], max(((int *)&bboxmax)[j], ((int *)&pts2[i])[j]));
		}
	}
	//printf("MIN X %d MIN Y %d MAX X %d MAX Y %d\n", bboxmin.x, bboxmin.y, bboxmax.x, bboxmax.y);
	for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++)
	{
		for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++)
		{
			t_point_3d bc_screen = barycentric(pts2, &p);
			if (bc_screen.x >= 0 && bc_screen.y >= 0 && bc_screen.z >= 0)
				sdl_put_pixel(eng->surface, p.x, p.y, color);
		}
	}
}

/*
void			engine_triangle(t_engine *eng, t_player *plr, t_polygone *t)
{
	t_tric		trg;
	int 		color;

	trg.t0 = (t_fix_point_3d){t->vertices_array[2].x, t->vertices_array[2].y, t->vertices_array[2].z};
	trg.t1 = (t_fix_point_3d){t->vertices_array[1].x, t->vertices_array[1].y, t->vertices_array[1].z};
	trg.t2 = (t_fix_point_3d){t->vertices_array[0].x, t->vertices_array[0].y, t->vertices_array[0].z};
	if (trg.t0.y == trg.t1.y && trg.t0.y == trg.t2.y)
		return ;
	if (trg.t0.y > trg.t1.y)
		point_swap(&(trg.t0), &(trg.t1));
	if (trg.t0.y > trg.t2.y)
		point_swap(&(trg.t0), &(trg.t2));
	if (trg.t1.y > trg.t2.y)
		point_swap(&(trg.t1), &(trg.t2));
	trg.total_height = ((trg.t2.y) - (trg.t0.y));
	trg.i = 0;
	color = get_rgb(((t->color) >> 16), ((t->color) >> 8), ((t->color)), 255);
	while (trg.i < trg.total_height)
	{
		trg.second_half = trg.i > (trg.t1.y - trg.t0.y) || trg.t1.y == trg.t0.y;
		trg.segment_height = trg.second_half ? trg.t2.y - trg.t1.y : trg.t1.y - trg.t0.y;
		trg.alpha = (double)trg.i / trg.total_height;
		trg.beta = (double)(trg.i - (trg.second_half ? trg.t1.y - trg.t0.y : 0)) / trg.segment_height;
		trg.a.x = trg.t0.x + (trg.t2.x - trg.t0.x) * trg.alpha;
		trg.a.y = trg.t0.y + (trg.t2.y - trg.t0.y) * trg.alpha;
		trg.a.z = trg.t0.z + (trg.t2.z - trg.t0.z) * trg.alpha;
		trg.b.x = trg.second_half ? trg.t1.x + (trg.t2.x - trg.t1.x) * trg.beta : trg.t0.x + (trg.t1.x - trg.t0.x) * trg.beta;
		trg.b.y = trg.second_half ? trg.t1.y + (trg.t2.y - trg.t1.y) * trg.beta : trg.t0.y + (trg.t1.y - trg.t0.y) * trg.beta;
		trg.b.z = trg.second_half ? trg.t1.z + (trg.t2.z - trg.t1.z) * trg.beta : trg.t0.z + (trg.t1.z - trg.t0.z) * trg.beta;
		if (trg.a.x > trg.b.x)
			point_swap(&trg.a, &trg.b);
		trg.j = trg.a.x;
		while (trg.j <= trg.b.x)
		{
			trg.phi = trg.b.x == trg.a.x ? 1.0 : ((double)(trg.j - trg.a.x)) / ((double)(trg.b.x - trg.a.x));
			trg.p.x = trg.a.x + (trg.b.x - trg.a.x) * trg.phi;
			trg.p.y = trg.a.y + (trg.b.y - trg.a.y) * trg.phi;
			trg.p.z = trg.a.z + (trg.b.z - trg.a.z) * trg.phi;
			if (((trg.p.x >= 0 && trg.p.x < WIDTH) && (trg.p.y >= 0 && trg.p.y < HEIGHT))
			&& (eng->z_buff[trg.p.x + trg.p.y * WIDTH] < trg.p.z))
			{
				eng->z_buff[trg.p.x + trg.p.y * WIDTH] = trg.p.z;
				sdl_put_pixel(eng->surface, trg.p.x, trg.p.y, color);
			}
			trg.j++;
		}
		trg.i++;
	}
}
*/
