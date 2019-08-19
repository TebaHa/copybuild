/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:19:22 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/19 20:19:41 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# define WIDTH 1400
# define HEIGHT 900
# define TWODIM 2
# define THREEDIM 3
# define PLAYERSTARTZ 0
# define MAXSECTORS 32
# define hfov (0.83f * HEIGHT) // Affects the horizontal field of vision
# define vfov (0.1f * HEIGHT) // Affects the vertical field of vision
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
# define min(a,b)	(((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
# define max(a,b)	(((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
# define clamp(a, mi, ma)	min(max(a,mi),ma) // clamp: Clamp value into set range.
# define vxs(x0,y0, x1,y1)	((x0)*(y1) - (x1)*(y0)) // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
# define Overlap(a0, a1, b0, b1)	(min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
# define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3)	(Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
# define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
# define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((t_point_2d) { \
	vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
	vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })
# define Yaw(y, z) (y + z)
# define GAIN 0.5
# define KOEFF -1

/* INIT AND UNINIT ENGINE */
//void			uninitengine(void);

typedef	struct		s_fix_point_3d
{
	int				x;
	int				y;
	int				z;
}					t_fix_point_3d;

typedef	struct		s_fix_point_2d
{
	int				x;
	int				y;
}					t_fix_point_2d;

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
	t_point_3d		norm;
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
	int				duckcheck;
	int				running;
	int				fakefall;
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
	int				*z_buff;
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
	t_fix_point_3d	a;
	t_fix_point_3d	b;
	t_fix_point_3d	t0;
	t_fix_point_3d	t1;
	t_fix_point_3d	t2;
	double			alpha;
	double			beta;
	double			intensity;
	double			phi;
	t_fix_point_3d	p;
	int				offsetx;
	int				offsety;
}					t_tric;

typedef struct				s_bcontex
{
	int						steep;
	double					dx;
	double					dy;
	int						error2;
	int						derror2;
	int						x;
	int						y;
	t_point_3d				b;
	t_point_3d				e;
}							t_bcontex;

void			engine_sdl_init(t_engine **eng);
void			engine_sdl_uninit(t_engine *eng);
void			engine_draw_line(t_engine *eng, t_point_2d a, t_point_2d b, int color);
void			engine_render_object(t_engine *eng, t_object obj, t_player *plr);
void			engine_render_frame(t_engine *eng);
void			engine_render_world(t_engine *eng, t_player *plr, int *rendered);
void			sdl_clear_window(SDL_Surface *surf);
void			sdl_put_pixel(SDL_Surface *surf, int x, int y, int color);
void			error_handler(char *error_type, const char *str_error, t_engine *eng);
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
void			engine_render_wall(t_engine *eng, t_polygone *polygone, t_player *plr, int *ytop, int *ybottom, int portal, int *rendered, int sect);
void			point_swap_3(t_fix_point_3d *t0, t_fix_point_3d *t1);
void			point_swap_2(t_fix_point_2d *t0, t_fix_point_2d *t1);
int				get_rgb(int r, int g, int b, int a);
float			edge_function(t_point_3d *a, t_point_3d *b, t_point_3d *c);
void			zbuffer_zero(int *zbuffer);

float			percent(int start, int end, int current);
int				get_light(int start, int end, float percentage);
int				get_color(int current, int start,
										int end, int colors[2]);

void			swapper(t_point_3d *a, t_point_3d *b, int *steep);
t_bcontex		bresenham_init(t_point_3d *beg, t_point_3d *end);
t_bcontex		bresenham_init(t_point_3d *beg, t_point_3d *end);
void			bresenham_put_pixel(t_bcontex *c,
								t_engine *eng, int color, int zmax);
void			bresenham_line(t_point_3d *beg, t_point_3d *end,
							t_engine *eng, int color);
void			triangle_lines(t_polygone *t, t_engine *eng);
void			engine_rasterize_triangle(t_engine *eng, t_player *plr, t_polygone *t);
void			ft_swap(float *a, float *b);
t_point_3d		engine_barycentric(t_fix_point_2d pts[3], t_fix_point_2d *p);
t_point_3d		engine_cross(t_point_3d a, t_point_3d b);

t_point_3d		cross_vec3(t_point_3d v1, t_point_3d v2);
t_point_3d		create_vector(t_point_3d *a, t_point_3d *b);
double			magnitude(t_point_3d *normal);
void			normalize_vec3(t_point_3d *normal);
t_point_3d		calc_normal(t_polygone *poly);
void			fill_box(t_engine *eng, t_fix_point_2d p, int offsetx, int offsety, int color);
void			fill_triangle(t_engine *eng, t_fix_point_2d a, t_fix_point_2d b, t_fix_point_2d c, int color);
void			full_check_fill_box(t_engine *eng, t_fix_point_2d p, int offsetx, int offsety, t_fix_point_2d pts2[3], int color);
void			check_box(t_engine *eng, t_fix_point_2d p, int offsetx, int offsety, t_fix_point_2d pts2[3], int color);
int				check_ractangle(t_engine *eng, t_fix_point_2d start, int sizex, int sizey, t_fix_point_2d pts2[3], int color);
void			square_check_fill_box(t_engine *eng, t_fix_point_2d p, int offsetx, int offsety, t_fix_point_2d pts2[3], int color);
void			engine_bw_procedural_texture(t_engine *eng, t_fix_point_3d a);
double			engine_gain(double gain, int t);
double			engine_bias(double b, int t);
void			engine_render_polygone(t_engine *eng, t_player *plr, t_polygone *wall, int *ytop, int *ybottom);
void			engine_vline(t_engine *eng, t_fix_point_3d a, t_fix_point_3d b, int color);

#endif
