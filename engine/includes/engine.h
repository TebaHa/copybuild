/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:19:22 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/11 21:17:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# define WIDTH 1024
# define HEIGHT 780
# define TWODIM 2
# define THREEDIM 3
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <libft.h>
# include <stdio.h>
# include <SDL2/SDL.h>
# define hfov (0.73f * HEIGHT) // Affects the horizontal field of vision
# define vfov (0.2f * HEIGHT) // Affects the vertical field of vision

struct		xy
{
	float	x;
	float	y;
 };
// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
#define min(a,b)	(((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)	(((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)	min(max(a,mi),ma) // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)	((x0)*(y1) - (x1)*(y0)) // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0,a1,b0,b1)	(min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3)	(Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })
#define Yaw(y,z) (y + z)

/* INIT AND UNINIT ENGINE */
//void			uninitengine(void);

typedef struct		s_vec4
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec4;

typedef struct		s_mat4
{
	float			values[4][4];
}					t_mat4;

typedef	struct		s_point_2d
{
	float			x;
	float			y;
}					t_point_2d;

typedef	struct		s_point_3d
{
	float			x;
	float			y;
	float			z;
}					t_point_3d;

typedef struct		s_polygone
{
	t_point_3d		*vertices;
	int				vertices_size;
}					t_polygone;

typedef struct		s_object
{
	int				sector;
	t_polygone		*polies_array;
}					t_object;

typedef	struct		s_sector
{
	t_object		*objects_array;
	int				objects_size;
}					t_sector;

typedef	struct		s_world
{
	t_sector		*sectors_array;
}					t_world;

typedef	struct		s_control
{
	int				wasd[4];
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
}					t_control;

typedef	struct		s_player
{
	t_control		controller;
	t_point_3d		position; // current position
	t_point_3d		velocity; // current motion vector
	float			angle; // view angle
	unsigned		cursector; // sectornumber
}					t_player;

typedef struct		s_engine
{
	SDL_Event 		event;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_world			*world;
	short			view_type;
}					t_engine;

typedef struct		s_item
{
	int				sectorno;
	int				sx1;
	int				sx2;
}					t_item;

void			engine_sdl_init(t_engine **eng);
void			engine_sdl_uninit(t_engine *eng);
void			engine_draw_line(t_engine *eng, t_point_2d a, t_point_2d b, int color);

void			engine_render_object(t_engine *eng, t_object obj, t_player *plr);
void			engine_render_frame(t_engine *eng);
void			engine_render_sector(t_engine *eng, t_sector *sect, t_player *plr);

void			sdl_clear_window(SDL_Renderer *ren);
void			sdl_put_pixel(SDL_Renderer *ren, int x, int y, int color);
void			error_handler(char *error_type, const char *str_error, t_engine *eng);


void			engine_render_polygone(t_engine *eng, t_polygone polygone, t_player *plr, int *ytop, int *ybottom);

void			engine_create_test_world(t_world **world);
t_object		engine_create_obj_wall(int portal, t_point_3d a, t_point_3d b, t_point_3d c, t_point_3d d);

t_point_3d		engine_count_perspective(t_point_3d a, int c);
t_mat4			getzeroaffinmat4(void);
t_vec4			matrix_on_vec_multiply(t_mat4 a, t_vec4 b);

#endif
