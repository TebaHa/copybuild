/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:19:22 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/03 16:17:19 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# define WIDTH 1024
# define HEIGHT 720
# define TWODIM 2
# define THREEDIM 3
# define PLAYERSTARTZ 0
# define MAXSECTORS 32
# define hfov (0.73f * HEIGHT) // Affects the horizontal field of vision
# define vfov (0.2f * HEIGHT) // Affects the vertical field of vision
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <libft.h>
# include <SDL2/SDL.h>

typedef	struct		s_point_2d
{
	float			x;
	float			y;
}					t_point_2d;

// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
#define min(a,b)	(((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)	(((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi, ma)	min(max(a,mi),ma) // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)	((x0)*(y1) - (x1)*(y0)) // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0, a1, b0, b1)	(min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3)	(Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((t_point_2d) { \
	vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
	vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })
#define Yaw(y, z) (y + z)

/* INIT AND UNINIT ENGINE */
//void			uninitengine(void);

typedef	struct		s_point_3d
{
	int				id;
	float			x;
	float			y;
	float			z;
}					t_point_3d;

typedef struct		s_polygone
{
	t_point_3d		*vertices_array;
	int				vertices_count;
	int				id;
	int				type;
	int				color;
}					t_polygone;

typedef struct		s_object
{
	t_polygone		*polies_array;
	int				portal;
	int				id;
	int				polies_count;
}					t_object;

typedef	struct		s_sector
{
	t_object		*objects_array;
	int				objects_count;
	int				id;
	int				floor;
	int				ceil;
}					t_sector;

typedef	struct		s_world
{
	t_sector		*sectors_array;
	int				sectors_count;
	int				*renderqueue;
	int				id;
}					t_world;

typedef	struct		s_control
{
	int				wasd[4];
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
	int				running;
}					t_control;

typedef	struct		s_player
{
	t_control		controller;
	t_point_3d		position; // current position
	t_point_3d		velocity; // current motion vector
	float			angle; // view angle
	float			cosangle;
	float			sinangle;
	float			yaw;
	unsigned		cursector; // sectornumber
}					t_player;

typedef struct		s_stats
{
	int				vertexes_count;
	int				polies_count;
	int				objects_count;
	int				sectors_count;
}					t_stats;

typedef struct		s_engine
{
	SDL_Event 		event;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface 	*surface;
	t_world			*world;
	short			view_type;
	t_stats			stats;
}					t_engine;

typedef struct		s_item
{
	int				sectorno;
	int				sx1;
	int				sx2;
}					t_item;

typedef struct		s_tric
{
	int				total_height;
	int				second_half;
	int				i;
	int				j;
	int				segment_height;
	t_point_3d		a;
	t_point_3d		b;
	t_point_3d		t0;
	t_point_3d		t1;
	t_point_3d		t2;
	double			alpha;
	double			beta;
	double			intensity;
	double			phi;
	t_point_3d		p;
	int				offsetx;
	int				offsety;
}					t_tric;


void			engine_sdl_init(t_engine **eng);
void			engine_sdl_uninit(t_engine *eng);
void			engine_draw_line(t_engine *eng, t_point_2d a, t_point_2d b, int color);
void			engine_render_object(t_engine *eng, t_object obj, t_player *plr);
void			engine_render_frame(t_engine *eng);
void			engine_render_world(t_engine *eng, t_player *plr, int *rendered);
void			sdl_clear_window(SDL_Surface *surf);
void			sdl_put_pixel(SDL_Surface *surf, int x, int y, int color);
void			error_handler(char *error_type, const char *str_error, t_engine *eng);
void			engine_render_polygone(t_engine *eng, t_polygone *polygone, t_player *plr, int *ytop, int *ybottom, int portal, int *rendered);
void			engine_create_test_world(t_world **world);
void			engine_push_renderstack(int *renderqueue, int sector_id);
void			engine_clear_renderstack(int *renderqueue);
void			engine_create_renderstack(t_engine *eng, int render_id, int *rendered);
int				engine_pop_renderstack(int *renderqueue);
int				engine_object_get_sector(t_world *world, t_point_3d pos);
t_object		engine_create_obj_wall(int portal, t_point_3d a, t_point_3d b, t_point_3d c, t_point_3d d);
t_point_3d		engine_count_perspective(t_point_3d a, int c);

t_point_3d		*util_create_point_3d(float x, float y, float z);
t_world			*util_create_world(int id, int sector_count);
t_sector		*util_create_sector(int id, int floor, int ceil, int object_count);
t_object		*util_create_object(int id, int portal, int polies_count);
t_polygone		*util_create_polygone(int id, int type, int vertex_count);
void			util_release_char_matrix(char **mtrx);

t_world			*engine_read_world_from_file(t_engine *eng, char **json_splited);
char			*engine_read_level_file(char *filename);
t_point_3d		*engine_read_vertexes_from_file(t_engine *eng, char **json_splited);
t_polygone		*engine_read_polygones_from_file(t_engine *eng, t_point_3d *vertex_array, char **json_splited);
t_object		*engine_read_objects_from_file(t_engine *eng, t_polygone *polies_array, char **json_splited);
t_sector		*engine_read_sectors_from_file(t_engine *eng, t_object *sector_array, char **json_splited);

t_point_3d		util_get_vertex_from_buff_by_id(int id, int size, t_point_3d *vertexes);
t_polygone		util_get_polygone_from_buff_by_id(int id, int size, t_polygone *sectors);
t_object		util_get_object_from_buff_by_id(int id, int size, t_object *objects);

void			util_release_read_buffers(t_point_3d *vertex_buff, t_polygone *polies_buff,
								t_object *object_buff);
void			util_release_sectors_buffer(t_sector *sector_buff, int size);
void			util_release_objects_buffer(t_object *object_buff, int size);
void			util_release_polies_buffer(t_polygone *polies_buff, int size);
void			util_release_vertex_buffer(t_point_3d *vertex_buff);
void			util_release_world(t_world *world);
void			engine_create_world_from_file(t_engine *eng, char *filename);
void			engine_clear_frame(t_engine *eng);

void			engine_triangle(t_engine *eng, t_player *plr, t_polygone *t);
int				engine_init_triangle(t_polygone *t, t_tric *trg);
void			engine_do_draw(t_engine *eng, t_player *plr, t_tric *trg, int color);
void			engine_do_calc(t_tric *trg);
void			engine_render_wall(t_engine *eng, t_player *plr, t_polygone *wall, int *ytop, int *ybottom);
void			point_swap(t_point_3d *t0, t_point_3d *t1);
int				get_rgb(int r, int g, int b, int a);

#endif
