/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:19:22 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/03 11:59:34 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# include <unistd.h>
# include <math.h>
# include <libft.h>
# include <SDL2/SDL.h>
# include <dirent.h>
# include <SDL2/SDL_ttf.h>
# define ENGINE_H
# define WIDTH 1024
# define HEIGHT 768
# define TWODIM 2
# define THREEDIM 3
# define PLAYERSTARTZ 0
# define MAXSECTORS 32
# define hfov (0.83f * HEIGHT / WIDTH)
# define vfov (0.2f)
# define TEXTURE_PACK_PATH "../game/resources/images/"
# define TEXTURE_SPRITE_PATH "../game/resources/sprites/"
# define GAME_PATH "../game/resources/levels/1.lvl"
# define PARSING_ERROR 40
# define READING_ERROR 41
# define CYCLE_READING_ERROR 42
# define PARSING_ERROR_TEXTURE	"!purple"
# define PARSING_ERROR_SPRITE	"!teal"
# define THREAD_POOL_SIZE 4
# define DELAY 15
# define DEFAULT_SPRITE_DELAY	10
# define FIRERATE 10

// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
# define min(a,b)	(((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
# define max(a,b)	(((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
# define clamp(a, mi, ma)	min(max(a,mi),ma) // clamp: Clamp value into set range.
# define vxs(x0,y0, x1,y1)	((x0)*(y1) - (x1)*(y0)) // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
# define Overlap(a0, a1, b0, b1)	(min(a0, a1) <= max(b0, b1) && min(b0, b1) <= max(a0, a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
# define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3)	(Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
# define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
# define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((t_point_2d) { \
	vxs(vxs(x1,y1, x2,y2), (x1) - (x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
	vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })
# define Scaler_Init(a,b,c,d,f) \
	{ d + (b-1 - a) * (f-d) / (c-a), ((f<d) ^ (c<a)) ? -1 : 1, \
		abs(f-d), abs(c-a), (int)((b - 1 - a) * abs(f-d)) % abs(c-a) }

typedef enum		e_sprite_type
{
	NOT_ANIMATBLE,
	ANIMATBLE
}					t_sprite_type;

typedef enum		e_player_state
{
	P_IDLE,
	P_FIRE,
	P_RELOAD
}					t_player_state;

typedef enum		e_sprt_obj_type
{
	STATIC_OBJECT,
	ROTATABLE_OBJECT
}					t_sprt_obj_type;

typedef struct		s_costil
{
	float			x;
	float			z;
}					t_costil;

typedef struct		s_scaler
{
	int result;
	int bop;
	int fd;
	int ca;
	int cache;
}					t_scaler;

typedef enum		e_bool
{
	false,
	true
}					t_bool;

typedef	struct		s_point_2d
{
	float			x;
	float			y;
}					t_point_2d;

typedef enum		e_alloc_type
{
	NO_ALLOCATION,
	SELF_ALLOCATED,
	STB_ALLOCATED
}					t_alloc_type;

typedef enum		e_enm_type
{
	MEDKIT,
	ARMOR,
	POWER_UP,
	RIFLE_AMMO,
	PLASMA_AMMO,
	PLASMA_GUN,
	BARREL,
	AFRIT,
	CACODEMON,
	IMP,

	ENEMY_NUM
}					t_enm_type;

typedef enum		e_enm_state
{
	E_IDLE,
	E_RUN,
	E_FIRE,
	E_HURT,
	E_DEAD,
	E_STATES_NUM
}					t_enm_state;

typedef enum		e_wpn_type
{
	RIFLE,
	PLASMA,
	WEAPON_NUM
}					t_wpn_type;

typedef enum		e_wpn_state
{
	W_IDLE,
	W_RUN,
	W_FIRE,
	W_NO_AMMO,
	W_RELOAD,
	W_HURT,
	W_STATES_NUM
}					t_wpn_state;

typedef enum		e_emo_state
{
	F_IDLE,
	F_HAPPY,
	F_LEFT,
	F_RIGHT,
	F_SHOOT,
	F_HURT,
	F_STATES_NUM
}					t_emo_state;

typedef enum		e_health_state
{
	H_100,
	H_80,
	H_60,
	H_40,
	H_20,
	H_0,
	H_STATES_NUM
}					t_health_state;

typedef enum		e_animtn_state
{
	STATIC,
	ANIMATE,
	CYCLE,
	PENDULUM
}					t_animtn_state;


typedef struct		s_image
{
	int				width;
	int				height;
	int				channels;
	size_t			size;
	uint8_t			*data;
	t_alloc_type	allocation_;
 }					t_image;

typedef struct		s_item
{
	int				sectorno;
	int				sx1;
	int				sx2;
}					t_item;

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
	t_point_3d		norm;
	int				vertices_count;
	int				id;
	int				type;
	int				color;
	t_image			*texture;
}					t_polygone;

typedef struct		s_sprite
{
	int				id;
	char 			*name;
	SDL_Surface		*surface;
	t_animtn_state	a_state;
	int 			frames_num;
	int 			frames_delay;
}					t_sprite;

typedef struct		s_wallobj
{
	int				id;
	t_point_2d		a;
	t_point_2d		b;
	float			z;
	float			abs_w;
	float			abs_h;
	int				timer;
	int				frame_num;
	t_sprite		*texture;
}					t_wallobj;

typedef struct		s_enemy
{
	int 			id;
	char 			*name;
	t_sprite		*anmtn[E_STATES_NUM];
}					t_enemy;

typedef struct		s_weapon
{
	int 			id;
	char 			*name;
	int 			ammo;
	int 			max_ammo;
	int 			containers;
	int 			frame;
	t_wpn_state 	state;
	t_sprite		*anmtn[W_STATES_NUM];
	t_sprite		*bullet_hole;
	struct s_weapon	*next;
	struct s_weapon	*prev;
}					t_weapon;

typedef struct		s_hud
{
	t_emo_state 	emo_state;
	t_health_state	health_state;
	t_sprite		*face[H_STATES_NUM][F_STATES_NUM];
}					t_hud;

typedef struct		s_sprobject
{
	int				id;
	int 			angle;
	t_enemy			*type;
	int 			frame;
	t_point_3d		position;
	t_enm_state 	state;
}					t_sprobject;

typedef struct		s_object
{
	t_polygone		*polies_array;
	int				portal;
	int				passble;
	int				id;
	int				polies_count;
	int				visible;
	int				status;
	t_wallobj		particles[128];
	t_image			*floor_wall_texture;
	t_image			*ceil_wall_texture;
}					t_object;

typedef struct		s_buff
{
	t_point_3d		*vertexes;
	t_sprite		*sprites;
	t_polygone		*polies;
	t_object		*objects;
	t_sprobject		*sprobjects;
	char 			**str;
}					t_buff;

typedef	struct		s_sector
{
	t_object		*objects_array;
	t_sprobject		*sprobjects_array;
	int				objects_count;
	int				sprobjects_count;
	int				id;
	int				floor;
	int				ceil;
	t_image			*ceil_texture;
	t_image			*floor_texture;
}					t_sector;

typedef	struct		s_world
{
	t_sector		*sectors_array;
	t_sector		*world_box;
	int				sectors_count;
	t_item			*renderqueue;
	int				checkqueue[MAXSECTORS];
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
	t_point_3d		real_position;
	t_weapon		*wpn;
	float			angle; // view angle
	float			cosangle;
	float			sinangle;
	float			yaw;
	unsigned		cursector; // sectornumber
	int				firetime;
	int				shoot;
	int				anim;
	int				delay;
	int				frame_num;
	t_player_state	plr_state;
}					t_player;

typedef struct		s_stats
{
	int				vertexes_count;
	int				polies_count;
	int				objects_count;
	int 			sprobjects_count;
	int				sectors_count;
	int 			textures_count;
	int 			skins_count;
	int 			sprites_count;
	int 			cycle_detector;
	int 			parsing_debug;
}					t_stats;

typedef struct		s_txtr_pkg
{
	t_image			texture;
	char			*filename;
}					t_txtr_pkg;

typedef struct		s_engine
{
	int				x;
	int				y;
	SDL_Event 		event;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_world			*world;
	short			view_type;
	t_stats			stats;
	int				*z_buff;
	t_weapon		*weapon[WEAPON_NUM];
	t_enemy			*enemy[ENEMY_NUM];
	t_hud			*hud;
	t_txtr_pkg		**texture_buffer;
	t_txtr_pkg		**sprites_buffer;
	t_sprobject		*tmp;
}					t_engine;

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

typedef struct		s_bcontex
{
	int				steep;
	double			dx;
	double			dy;
	int				error2;
	int				derror2;
	int				x;
	int				y;
	t_point_3d		b;
	t_point_3d		e;
}					t_bcontex;

typedef struct		s_thread_pool
{
	SDL_Thread		*thread;
	SDL_Surface 	*surface;
	int				*z_buff;
	int				value;
}					t_thread_pool;

typedef struct		s_line
{
	t_point_3d		a;
	t_point_3d		b;
}					t_line;

typedef struct		s_plane
{
	t_point_3d		p;
	t_point_3d		n;
}					t_plane;


void			engine_sdl_init(t_engine **eng);
void			engine_sdl_uninit(t_engine *eng);
void			engine_draw_line(t_engine *eng, t_point_2d a, t_point_2d b, int color);
void			engine_render_object(t_engine *eng, t_object obj, t_player *plr);
void			engine_render_frame(t_engine *eng, SDL_Surface 	*surf);
void			engine_render_world(t_engine *eng, t_player plr, SDL_Surface *surf, int *zbuff);
void			sdl_clear_window(SDL_Surface *surf);
void			sdl_put_pixel(SDL_Surface *surf, int x, int y, int color);
void			error_handler(char *error_type, const char *str_error, t_engine *eng);
void			engine_create_test_world(t_world **world);
void			engine_push_renderstack(t_item *renderqueue, t_item item);
void			engine_clear_renderstack(t_item *renderqueue);
void			engine_create_renderstack(t_engine *eng, int render_id, int *rendered);
t_item			engine_pop_renderstack(t_item *renderqueue);
int				engine_object_get_sector(t_world *world, t_point_3d pos, int start_sect);
t_object		engine_create_obj_wall(int portal, t_point_3d a, t_point_3d b, t_point_3d c, t_point_3d d);
t_point_3d		engine_count_perspective(t_point_3d a, int c);
void			util_release_sectors_buffer(t_sector *sector_buff, int size);
void			util_release_objects_buffer(t_object *object_buff, int size);
void			util_release_polies_buffer(t_polygone *polies_buff, int size);
void			util_release_vertex_buffer(t_point_3d *vertex_buff);
void			util_release_world(t_world *world);
void			engine_clear_frame(t_engine *eng);

void			engine_triangle(t_engine *eng, t_player *plr, t_polygone *t);
int				engine_init_triangle(t_polygone *t, t_tric *trg);
void			engine_do_draw(t_engine *eng, t_player *plr, t_tric *trg, int color);
void			engine_do_calc(t_tric *trg);
void			engine_render_wall(t_engine *eng, SDL_Surface *surf, t_polygone *polygone, t_player *plr, int *ytop, int *ybottom, int portal, t_item sect, int obj_id, int prev, int *zbuff);
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
								SDL_Surface *surf, int color, int zmax);
void			bresenham_line(t_point_3d *beg, t_point_3d *end,
							SDL_Surface *surf, int color);
void			triangle_lines(t_polygone *t, SDL_Surface *surf);
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
void			engine_vline(t_engine *eng, SDL_Surface *surf, t_fix_point_3d a, t_fix_point_3d b, int color);
void			engine_render_world_walls(t_engine *eng, t_polygone *polygone, t_player *plr, t_item sect);
void			engine_render_world_box(t_engine *eng, t_player *plr);
t_point_3d		calc_normal_dots(t_point_3d a, t_point_3d b, t_point_3d c);
void			engine_push_particlestack(t_object *obj, t_weapon *wpn, t_wallobj *particlestack, int *status, t_point_3d particle);
void			engine_push_checkstack(int *checkqueue, int item);
int				engine_pop_checkstack(int *checkqueue);
void			engine_clear_checkstack(int *checkqueue);
int				check_point_inside_box(t_point_3d a, t_object *obj, float ceil, float floor);
void			engine_render_particle(t_engine *eng, SDL_Surface *surf, t_wallobj *particle,  t_object *obj, int *ytop, int *ybottom, t_player *plr, t_item sect, int *zbuff);
void			get_relative_xy(t_engine *eng, t_fix_point_2d *p);
void			zbuff_zeroed(int *zbuff);
void			engine_render_rescale(SDL_Surface *surf, SDL_Surface *dest, int z, int *zbuff, t_fix_point_2d point, int newWidth, int newHeight);
void			animator_render_sprite_object(t_engine *eng, SDL_Surface *surf, t_player plr, t_sprobject *spr_obj, t_item sect, int *zbuff);
t_sprobject		*create_test_sprobj(t_engine *eng);
void			engine_vline_textured_sprite(t_engine *eng, SDL_Surface *surf, t_scaler ty, t_fix_point_3d a, t_fix_point_3d b, int txtx, int z, int *zbuff, t_sprite *texture);
void			engine_vline_textured_surface(t_engine *eng, SDL_Surface *surf, t_scaler ty, t_fix_point_3d a, t_fix_point_3d b, int txtx, int z, int *zbuff, SDL_Surface *texture);
void			switch_weapon(t_engine *eng, t_player *plr, int weapon_num);

/*
**Image-processing functions
*/
void			image_load(t_image *img, const char *fname);
void			image_create(t_image *img, int width, int height, int channels);
void			image_free(t_image *img);
t_image			load_textures(const char *fname);
int				scaler_next(t_scaler *i);
void			engine_vline_textured(t_engine *eng, SDL_Surface *surf, t_scaler ty, t_fix_point_3d a, t_fix_point_3d b, int txtx, int z, int *zbuff, t_image *texture);
void			move_player(t_engine *eng, t_player *plr, float dx, float dy, unsigned sect);
t_costil		relative_map_coordinate_to_absolute(t_player *plr, float map_y, float screen_x, float screen_y);
t_costil		ceiling_floor_screen_coordinates_to_map_coordinates(t_player *plr, float tz, float tx);
void			change_floor(t_engine *eng, int sect, int change);
void			change_ceil(t_engine *eng, int sect, int change);
void			engine_push_checkstack(int *stack, int sect);
int				engine_pop_checkstack(int *stack);
void			engine_clear_checkstack(int *stack);
t_image			*engine_cut_texture(t_image *world_texture, int xstart, int xsize, int ystart, int ysize);
void			game_stop_threads(t_thread_pool	*render_thread, int thread_count);
void			engine_draw_hud(t_engine *eng, t_player *plr, SDL_Surface *surf);
void			shoot(t_engine *eng, t_player *plr, int weapon_range);
int				intersect_3d_seg_plane(t_line s, t_plane pn, t_point_3d *res);

/*
**	---------------------------------------------------------------------------
**	Resources parsing functions start
*/

void 			engine_create_resources_from_file(t_engine *eng);
void			eng_read_sprites(t_engine *eng);
void			eng_read_textures(t_engine *eng);

void			eng_create_hud(t_engine *eng);
void			eng_create_face(t_engine *eng);
void			eng_create_face_100_0(t_engine *eng);

void			eng_create_weapons(t_engine *eng);
void 			eng_create_rifle(t_engine *eng);
void			eng_create_plasma(t_engine *eng);

void			eng_create_items(t_engine *eng);
void			eng_create_medkit(t_engine *eng);
void			eng_create_armor(t_engine *eng);
void			eng_create_powerup(t_engine *eng);
void			eng_create_rifle_ammo(t_engine *eng);
void			eng_create_plasma_ammo(t_engine *eng);
void			eng_create_plasma_gun(t_engine *eng);

void			eng_create_enemies(t_engine *eng);
void 			eng_create_barrel(t_engine *eng);
void 			eng_create_afrit(t_engine *eng);
void 			eng_create_cacodemon(t_engine *eng);
void 			eng_create_imp(t_engine *eng);

t_sprite		*util_get_sprite_from_buff_by_name(char *name, t_txtr_pkg *buff,
				int size);
char			*util_add_png_to_name(char *old_name);
char			*util_add_png_num_to_name(char *old_name, int num);
t_sprite		*util_create_sprite_by_name(t_engine *eng, char *str);

/*
**	Resources parsing functions end
**	===========================================================================
**	Parsing map functions
*/

void			util_release_char_matrix(char **mtrx);
void			util_release_read_buffers(t_buff *buff);
void			util_float10_data_filler(float *data, char *str);
void			util_int10_data_filler(int *data, char *str);
void			util_int16_data_filler(int *data, char *str);
void			util_parsing_error_count_handler(char *problem_from,
				char **str, int problems_number);
void			util_parsing_error_cant_find(char *problem, int id_problem);
void			util_parsing_error_lost_handler(char *problem, int id_problem,
				char *problem_from, int id_problem_from);
void			util_parsing_error_extra_data(char *problem, char *problem_from,
				char **str);
void			util_parsing_error_little_data(char *problem, char *problem_from,
				char **str);
void			util_parsing_error_not_digit(char *problem);
void			util_parsing_error_not_hex(char *problem);
void			util_parsing_error_no_cap(char *problem, t_engine *eng);
SDL_Surface		*util_transform_texture_to_sprite(t_image *texture);
SDL_Surface		*util_CreateRGBSurface(Uint32 flags, int width, int height,
				int depth);

char			**engine_read_level_file(char *filename);
void			engine_count_all_from_file(t_engine *eng, char **json_splited);

void			engine_read_world_from_file(t_engine *eng, char **json_splited);
void			engine_create_world_from_file(t_engine *eng, char *filename);
void			util_create_world(t_world **world, char **str);

t_point_3d		*engine_read_vertexes_from_file(t_engine *eng, char **json_splited);
void			util_create_point_3d(t_engine *eng, t_point_3d *point, char **str);
t_point_3d		util_get_vertex_from_buff_by_id(int id, int size,
				t_point_3d *vertexes, int polygone_id);

t_polygone		*engine_read_polygones_from_file(t_engine *eng, t_buff buff);
void			util_create_polygone(t_engine *eng, t_polygone *polygone,
				t_point_3d *vertex_array, char **str);
t_polygone		util_get_polygone_from_buff_by_id(int id, int size,
				t_polygone *polies, int object_id);

t_object		*engine_read_objects_from_file(t_engine *eng, t_buff buff);
void			util_create_object(t_engine *eng, t_object *object,
				t_polygone *polygone_array, char **str);
t_object		util_get_object_from_buff_by_id(int id, int size,
				t_object *objects, int sector_id);

t_sprobject		*engine_read_sprobjects_from_file(t_engine *eng, t_buff buff);
void			util_create_sprobject(t_engine *eng, t_sprobject *sprobject,
				t_sprite *sprite_array, t_point_3d *vertex_array, char **str);
t_sprobject		util_get_sprobject_from_buff_by_id(int id, int size,
				t_sprobject *sprobjects, int sector_id);

void			engine_read_sectors_from_file(t_engine *eng, t_buff buff);
void			engine_read_worldbox_from_file(t_engine *eng, t_buff buff);
void			util_create_sector(t_engine *eng, t_buff buff,
				t_sector *sector, char **str);
void			util_create_sector_sprobjs(t_engine *eng, t_buff buff,
				t_sector *sector, char **str);

void			util_find_texture_by_name(t_image **dst, t_engine *eng,
				char *name);
void			util_parsing_error_no_texture(t_image **dst, t_engine *eng,
				char *name);

t_sprite		*engine_read_sprites_from_file(t_engine *eng, t_buff);
void			util_create_sprite(t_engine *eng, t_sprite *sprite,	char **str);
t_sprite		util_get_sprite_from_buff_by_id(int id, int size, t_sprite *sprites,
				int sprobj_id);
void			util_find_sprite_by_name(SDL_Surface *dst, t_engine *eng,
				char *name);
void			util_parsing_error_no_sprite(SDL_Surface *dst, t_engine *eng,
				char *name);

/*
**	Parsing map functions end
**	---------------------------------------------------------------------------
*/

# endif
