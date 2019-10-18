/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:19:22 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 20:33:32 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# include <unistd.h>
# include <math.h>
# include <libft.h>
# include <SDL.h>
# include <dirent.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# define ENGINE_H
# define WIDTH 1024
# define HEIGHT 768
# define TWODIM 2
# define THREEDIM 3
# define PLAYERSTARTZ 0
# define MAXSECTORS 32
# define hfov (1.0 * 0.83f * HEIGHT / WIDTH)
# define vfov (1.0 * 0.2f)
# define TEXTURE_PACK_PATH		"./game/resources/images/"
# define TEXTURE_SPRITE_PATH	"./game/resources/sprites/"
# define SOUND_PATH				"./game/resources/sounds/"
# define GAME_PATH				"./game/resources/levels/1.lvl"
# define FONT_PATH				"./game/resources/fonts/SEASRN__.ttf"
# define PARSING_ERROR 40
# define READING_ERROR 41
# define CYCLE_READING_ERROR 42
# define PARSING_ERROR_TEXTURE	"!purple"
# define PARSING_ERROR_SPRITE	"!teal"
# define THREAD_POOL_SIZE	4
# define DELAY 15
# define DEFAULT_SPRITE_DELAY	10
# define FIRERATE 30
# define BACKGROUND_MUSIC_VOLUME	0.1
# define GAME_SOUNDS_VOLUME			1

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
	int			result;
	int			bop;
	int			fd;
	int			ca;
	int			cache;
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

typedef enum		e_sound_ch
{
	S_BACKGROUND,
	S_WEAPON_SHOT,
	S_WEAPON_EXTRA,
	S_PLAYER,
	S_ENEMY_1,
	S_ENEMY_2,
	SOUNDS_NUM
}					t_sound_ch;

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

typedef enum		e_crc_state
{
	CRC_MISSING,
	CRC_ZERO,
	CRC_INCORRECT,
	CRC_MULTIPLE,
	CRC_NOT_IN_END,
	CRC_OK
}					t_crc_state;

typedef struct		s_int_4
{
	int				x;
	int				y;
	int				offsets;
	int				offseti;
	unsigned		*pix;
}					t_int_4;

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

typedef struct		s_item_sprts
{
	t_item			sect_id;
	int				ytop[WIDTH];
	int				ybottom[WIDTH];
}					t_item_sprts;

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
	SDL_Surface		**surface;
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
	int				size;
}					t_wallobj;

typedef struct		s_enemy
{
	int 			id;
	char 			*name;
	Mix_Chunk		*death_sound;
	t_sprite		*anmtn[E_STATES_NUM];
}					t_enemy;

typedef struct		s_weapon
{
	int 			id;
	char 			*name;
	int 			ammo;
	int 			max_ammo;
	int 			containers;
	int 			cooldown;
	t_wpn_state 	state;
	t_sprite		*anmtn[W_STATES_NUM];
	t_sprite		*bullet_hole;
	Mix_Chunk		*shot_sound;
	struct s_weapon	*next;
	struct s_weapon	*prev;
}					t_weapon;

typedef struct		s_hud
{
	t_emo_state 	emo_state;
	t_health_state	health_state;
	t_sprite		*health;
	t_sprite		*armor;
	t_sprite		*ammo;
	t_sprite		*face[H_STATES_NUM][F_STATES_NUM];
}					t_hud;

typedef struct		s_sprobject
{
	int				id;
	int 			angle;
	t_enemy			*type;
	t_enm_type		enum_type;
	int 			frame;
	t_point_3d		position;
	t_enm_state 	state;
	t_bool			norender;
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
	int				*order;
	float			*dist;
	int				id;
	int				floor;
	int				ceil;
	t_image			*ceil_texture;
	t_image			*floor_texture;
	t_item_sprts	item_sprts;
}					t_sector;

typedef	struct		s_world
{
	t_sector		*sectors_array;
	t_sector		*world_box;
	int				sectors_count;
	t_item			*renderstack;
	t_item_sprts	**sprite_renderstack;
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
	Mix_Chunk		*steps_sound;
	t_player_state	plr_state;
	int				health;
	int				armor;
}					t_player;

typedef struct		s_stats
{
	int 			worlds_count;
	int				vertexes_count;
	int				polies_count;
	int				objects_count;
	int 			sprobjects_count;
	int				sectors_count;
	int 			textures_count;
	int 			skins_count;
	int 			sprites_count;
	int 			cycle_detector;
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
	TTF_Font		*font;
	Mix_Chunk		*background_music;
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
	float			alpha;
	float			beta;
	float			intensity;
	float			phi;
	t_fix_point_3d	p;
	int				offsetx;
	int				offsety;
}					t_tric;

typedef struct		s_bcontex
{
	int				steep;
	float			dx;
	float			dy;
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

typedef struct		s_mixer_thread
{
	Mix_Chunk		*sound_name;
	t_sound_ch		channel;
}					t_mixer_thread;

typedef struct		s_spr_info
{
	int				*order;
	float			*dist;
	int				amount;
}					t_spr_info;

typedef struct		s_wall_help1
{
	float			nearz;
	float			farz;
	float			nearside;
	float			farside;
	t_point_2d		i1;
	t_point_2d		i2;
	t_point_2d		org1;
	t_point_2d		org2;
}					t_wall_help1;

typedef struct		s_wall_help2
{
	t_polygone		*polygone;
	t_player		*plr;
	int				ytop[WIDTH];
	int				ybottom[WIDTH];
	int				portal;
	t_item			sect;
	int				obj_id;
	int				prev;
}					t_wall_help2;

typedef struct		s_wall_help3
{
	t_point_2d		t1;
	t_point_2d		t2;
	int				push;
	int				u0;
	int				u1;
}					t_wall_help3;

typedef struct		s_wall_mai_data
{
	float			xscale1;
	float			yscale1;
	float			xscale2;
	float			yscale2;
	int				x1;
	int				x2;
	float			yceil;
	float			yfloor;
	float			nyceil;
	float			nyfloor;
	int				y1a;
	int				y1b;
	int				y2a;
	int				y2b;
	int				ny1a;
	int				ny1b;
	int				ny2a;
	int				ny2b;
	int				beginx;
	int				endx;
	t_scaler		ya_int;
	t_scaler		yb_int;
	t_scaler		nya_int;
	t_scaler		nyb_int;
	int				ya;
	int				yb;
	int				cya;
	int				cyb;
	int				txtx;
	t_image			*tex;
	int				nya;
	int				nyb;
	int				cnya;
	int				cnyb;
}					t_wall_mai_data;

typedef struct		s_wall_cycle
{
	t_image			*tex;
	float			hei;
	t_costil		pnts;
	int				y;
	int				x;
	unsigned		txtx;
	unsigned		txtz;
	int				offset;
	int8_t			red;
	int8_t			green;
	int8_t			blue;
}					t_wall_cycle;

typedef struct		s_wall_clinks
{
	t_engine		*eng;
	SDL_Surface		*surf;
	t_wall_mai_data	*mdata;
	t_wall_help2	*data;
	t_wall_help3	*data_help;
	t_wall_cycle	*cycler;
}					t_wall_clinks;

typedef struct		s_sorter
{
	int		gap;
	int		j;
	int		i;
	t_bool	swapped;
}					t_sorter;

typedef struct		s_read_data
{
	int				i;
	int				real_i;
	DIR				*d;
	struct dirent	*dir;
	int				count;
	char			*buffer_name;
}					t_read_data;

typedef struct		s_shoot_data
{
	t_point_3d		int_p;
	t_line			shoot;
	t_plane			plane;
	t_sector		*sect;
	int				sect_id;
	int				prev;
	int				i;
	int				res;
	int				hit;
	float			angle_xy;
	float			angle_z;
	float			dx;
	float			dy;
	float			dz;
}					t_shoot_data;

typedef struct		s_surf_data
{
	int				*pix;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	alpha;
	int				tx;
	int				ty;
	int				x;
	int				y;
}					t_surf_data;

typedef struct		s_find_obj
{
	int				check_stack[MAXSECTORS];
	int				checked_array[MAXSECTORS];
	int				res;
	int				cursect;
	int				i;
	int				j;
	int				k;
}					t_find_obj;

typedef struct		s_sh_part
{
	t_wallobj		w_partcle;
	float			dx1;
	float			dy1;
	float			dx2;
	float			dy2;
	float			dist1;
	float			dist2;
	float			half_w;
}					t_sh_part;

typedef struct		s_vline1
{
	int				y1;
	int				y2;
	int				y;
	unsigned		txty;
	unsigned		offset;
	int8_t			red;
	int8_t			green;
	int8_t			blue;
	int				color;
	int				*pixd;
	uint8_t			*pixs;
}					t_vline1;

typedef struct		s_vline1_in
{
	t_fix_point_3d	a;
	t_fix_point_3d	b;
	int				txtx;
}					t_vline1_in;

void				engine_sdl_init(t_engine **eng);
void				engine_sdl_uninit(t_engine *eng);
void				engine_draw_line(t_engine *eng, t_point_2d a, t_point_2d b, int color);
void				engine_render_object(t_engine *eng, t_object obj, t_player *plr);
void				engine_render_frame(t_engine *eng, SDL_Surface 	*surf);
void				engine_render_world(t_engine *eng, t_player plr, SDL_Surface *surf);
void				sdl_clear_window(SDL_Surface *surf);
void				sdl_put_pixel(SDL_Surface *surf, int x, int y, int color);
void				error_handler(char *error_type, const char *str_error, t_engine *eng);
void				engine_create_test_world(t_world **world);
void				engine_push_renderstack(t_item *renderqueue, t_item item);
void				engine_clear_renderstack(t_item *renderqueue);
void				engine_create_renderstack(t_engine *eng, int render_id, int *rendered);
t_item				engine_pop_renderstack(t_item *renderqueue);
int					engine_object_get_sector(t_world *world, t_point_3d pos, int start_sect);
t_object			engine_create_obj_wall(int portal, t_point_3d a, t_point_3d b, t_point_3d c, t_point_3d d);
t_point_3d			engine_count_perspective(t_point_3d a, int c);
void				util_release_sectors_buffer(t_sector *sector_buff, int size);
void				util_release_objects_buffer(t_object *object_buff, int size);
void				util_release_polies_buffer(t_polygone *polies_buff, int size);
void				util_release_vertex_buffer(t_point_3d *vertex_buff);
void				util_release_world(t_world *world);
void				engine_present_and_clear_frame(t_engine *eng);
int					intersect_sect(t_point_2d a, t_point_2d b, t_point_2d pos);

void				eng_read_sprite(t_engine *eng, t_txtr_pkg ***text_buff, int *stats, char *path);
void				engine_triangle(t_engine *eng, t_player *plr, t_polygone *t);
int					engine_init_triangle(t_polygone *t, t_tric *trg);
void				engine_do_draw(t_engine *eng, t_player *plr, t_tric *trg, int color);
void				engine_do_calc(t_tric *trg);
void				engine_render_wall(t_engine *eng, SDL_Surface *surf, t_wall_help2 *data2);
void				point_swap_3(t_fix_point_3d *t0, t_fix_point_3d *t1);
void				point_swap_2(t_fix_point_2d *t0, t_fix_point_2d *t1);
int					get_rgb(int r, int g, int b, int a);
float				edge_function(t_point_3d *a, t_point_3d *b, t_point_3d *c);
void				zbuffer_zero(int *zbuffer);

float				percent(int start, int end, int current);
int					get_light(int start, int end, float percentage);
int					get_color(int current, int start,
										int end, int colors[2]);

void				engine_render_wall_recount_intersect(t_polygone *polygone, t_point_2d *t1, t_point_2d *t2, int *u[2]);
void				engine_render_wall_recount_intersect_help(t_wall_help1 *data,
					t_point_2d *t1, t_point_2d *t2);
void				*engine_render_wall_count_values(t_engine *eng,
					t_wall_help3 *data_help, t_wall_help2 *data, t_wall_mai_data *mdata);

void				swapper(t_point_3d *a, t_point_3d *b, int *steep);
t_bcontex			bresenham_init(t_point_3d *beg, t_point_3d *end);
t_bcontex			bresenham_init(t_point_3d *beg, t_point_3d *end);
void				bresenham_put_pixel(t_bcontex *c,
								SDL_Surface *surf, int color, int zmax);
void				bresenham_line(t_point_3d *beg, t_point_3d *end,
							SDL_Surface *surf, int color);
void				triangle_lines(t_polygone *t, SDL_Surface *surf);
void				engine_rasterize_triangle(t_engine *eng, t_player *plr, t_polygone *t);
void				ft_swap(float *a, float *b);
t_point_3d			engine_barycentric(t_fix_point_2d pts[3], t_fix_point_2d *p);
t_point_3d			engine_cross(t_point_3d a, t_point_3d b);

t_point_3d			cross_vec3(t_point_3d v1, t_point_3d v2);
t_point_3d			create_vector(t_point_3d *a, t_point_3d *b);
double				magnitude(t_point_3d *normal);
void				normalize_vec3(t_point_3d *normal);
t_point_3d			calc_normal(t_polygone *poly);
void				fill_box(t_engine *eng, t_fix_point_2d p, int offsetx, int offsety, int color);
void				fill_triangle(t_engine *eng, t_fix_point_2d a, t_fix_point_2d b, t_fix_point_2d c, int color);
void				full_check_fill_box(t_engine *eng, t_fix_point_2d p, int offsetx, int offsety, t_fix_point_2d pts2[3], int color);
void				check_box(t_engine *eng, t_fix_point_2d p, int offsetx, int offsety, t_fix_point_2d pts2[3], int color);
int					check_ractangle(t_engine *eng, t_fix_point_2d start, int sizex, int sizey, t_fix_point_2d pts2[3], int color);
void				square_check_fill_box(t_engine *eng, t_fix_point_2d p, int offsetx, int offsety, t_fix_point_2d pts2[3], int color);
void				engine_bw_procedural_texture(t_engine *eng, t_fix_point_3d a);
double				engine_gain(double gain, int t);
double				engine_bias(double b, int t);
void				engine_render_polygone(t_engine *eng, t_player *plr, t_polygone *wall, int *ytop, int *ybottom);
void				engine_vline(t_engine *eng, SDL_Surface *surf, t_fix_point_3d a, t_fix_point_3d b, int color);
void				engine_render_world_walls(t_engine *eng, t_polygone *polygone, t_player *plr, t_item sect);
void				engine_render_world_box(t_engine *eng, t_player *plr);
t_point_3d			calc_normal_dots(t_point_3d a, t_point_3d b, t_point_3d c);
void				engine_push_particlestack(t_object *obj, t_weapon *wpn,
					void *d[2], t_point_3d particle);
void				engine_push_checkstack(int *checkqueue, int item);
int					engine_pop_checkstack(int *checkqueue);
void				engine_clear_checkstack(int *checkqueue);
int					check_point_inside_box(t_point_3d a, t_object *obj, float ceil, float floor);
void				engine_render_particle(t_engine *eng, SDL_Surface *surf, t_wallobj *particle,  t_object *obj, t_player *plr, t_item sect);
void				get_relative_xy(t_engine *eng, t_fix_point_2d *p);
void				animator_render_sprite_object(t_engine *eng, SDL_Surface *surf, t_player plr, t_sprobject *spr_obj, t_item sect, int *zbuff);
t_sprobject			*create_test_sprobj(t_engine *eng);
void				engine_vline_textured_sprite(SDL_Surface *surf, t_scaler ty,
					t_vline1_in din, t_sprite *texture);
void				engine_vline_textured_surface(SDL_Surface *surf, t_scaler ty,
					t_vline1_in din, SDL_Surface *texture);
void				switch_weapon(t_engine *eng, t_player *plr, int weapon_num);
int					sound_play_thread_wrapper(void *ptr);
void				engine_render_wall_count_initial_point(t_polygone *polygone, t_player *plr,
					t_point_2d	*t1, t_point_2d	*t2);
void				engine_push_spriterenderstack(t_item_sprts **renderqueue, t_item_sprts *item);
void				engine_clear_spriterenderstack(t_item_sprts **renderqueue);
t_item_sprts		*engine_pop_spriterenderstack(t_item_sprts **renderqueue);
void				one_dim_zbuffers_copy(t_item_sprts *sprt, int *ytop, int *ybottom);

/*
** Image-processing functions
**
*/

void				image_load(t_image *img, const char *fname);
void				image_create(t_image *img, int width, int height, int channels);
void				image_free(t_image *img);
t_image				load_textures(const char *fname);
int					scaler_next(t_scaler *i);
void				engine_vline_textured(SDL_Surface *surf, t_scaler ty,
					t_vline1_in din, t_image *texture);
void				move_player(t_engine *eng, t_player *plr, float dx, float dy, unsigned sect);
t_costil			relative_map_coordinate_to_absolute(t_player *plr, float map_y, float screen_x, float screen_y);
t_costil			ceiling_floor_screen_coordinates_to_map_coordinates(t_player *plr, float tz, float tx);
void				change_floor(t_engine *eng, int sect, int change);
void				change_ceil(t_engine *eng, int sect, int change);
void				engine_push_checkstack(int *stack, int sect);
int					engine_pop_checkstack(int *stack);
void				engine_clear_checkstack(int *stack);
t_image				*engine_cut_texture(t_image *world_texture, int xstart, int xsize, int ystart, int ysize);
void				game_stop_threads(t_thread_pool	*render_thread, int thread_count);
void				engine_draw_hud(t_engine *eng, t_player *plr, SDL_Surface *surf);
void				shoot(t_engine *eng, t_player *plr, int weapon_range);
int					intersect_3d_seg_plane(t_line s, t_plane pn, t_point_3d *res);
void				draw_from_surface_to_surface(SDL_Surface *dest, SDL_Surface *src, int dx, int dy);

/*
**	---------------------------------------------------------------------------
**	Checksum functions start
*/

uint_least32_t	crc_calculate(char *buf, size_t len);
int				checksum_check(char *buf, char **buff_splited, size_t len);
int				checksum_check_line(char *buff, char *buff_splited,
				int *crc_count, int crc_pos);
void			util_parsing_error_wrong_crc(void);

/*
** 	Checksum functions end
**	===========================================================================
**	Resources parsing functions start
*/

void 			engine_create_resources_from_file(t_engine *eng);

void			eng_create_hud(t_engine *eng);
void			eng_create_face_100_60(t_engine *eng, t_hud *hud);
void			eng_create_face_40_0(t_engine *eng, t_hud *hud);

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

void			sound_mixer_init(void);
Mix_Chunk		*sound_init(char *name);
char			*util_add_wav_to_name(char *old_name);
void			sound_play(Mix_Chunk *sound_name, t_sound_ch channel);
void			sound_shoot(t_player *plr);
void			sound_free(t_engine *eng);
void			sound_player_control(t_player *plr);
void			eng_create_background_music(t_engine *eng);

void			infinite_loop(void);

/*
**	Resources parsing functions end
**	===========================================================================
**	Parsing map functions
*/

void			engine_parser(t_engine *eng, t_player *plr, char *filename);
void			engine_preparser(t_engine *eng, char **json_splited);
void			engine_count_all_from_file(t_stats *stats, char **buff);
char			**engine_read_level_file(char *filename);




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
void			util_parsing_error_no_lvl_file(char *problem);
void			util_parsing_error_extra_data(char *problem, char *problem_from,
				char **str);
void			util_parsing_error_little_data(char *problem, char *problem_from,
				char **str);
void			util_parsing_error_not_digit(char *problem);
void			util_parsing_error_not_hex(char *problem);
void			util_parsing_error_not_enough(char *problem);
void			util_parsing_error_repeats(char *problem, char *problem_from,
										   int id_problem);
void			util_parsing_error_no_cap(char *problem, t_engine *eng);
SDL_Surface		*util_transform_texture_to_sprite(t_image *texture);
SDL_Surface		*util_create_rgb_surface(Uint32 flags, int width, int height,
											int depth);

void			engine_check_plr_pos(t_world *world, t_player *plr);
void			util_parsing_error_player_outside(void);

void			engine_read_world_from_file(t_engine *eng, char **json_splited);
void			engine_create_world_from_file(t_engine *eng, t_player *plr, char *filename);
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
				t_buff *buff, char **str);
t_sprobject		util_get_sprobject_from_buff_by_id(int id, int size,
				t_sprobject *sprobjects, int sector_id);

void			engine_read_sectors_from_file(t_engine *eng, t_buff buff);
void			engine_read_worldbox_from_file(t_engine *eng, t_buff buff);
void			util_create_sector(t_engine *eng, t_buff buff,
				t_sector *sector, char **str);
void			util_create_sector_sprobjs(t_engine *eng, t_buff buff,
				t_sector *sector, char **str);
void			util_find_repeats_in_sector(t_sector *sector);
void			util_find_sprobjects_repeats_in_sector(t_sector *sector);

void			util_find_texture_by_name(t_image **dst, t_engine *eng,
				char *name);
void			util_parsing_error_no_texture(t_image **dst, t_engine *eng,
				char *name);

t_sprite		*engine_read_sprites_from_file(t_engine *eng, t_buff);
void			util_create_sprite(t_engine *eng, t_sprite *sprite,	char **str);
void			util_create_sprite_with_num(t_engine *eng, t_sprite *sprite,
				char **str, int srfc_count);
t_sprite		util_get_sprite_from_buff_by_id(int id, int size, t_sprite *sprites,
				int sprobj_id);
void			util_find_sprite_by_name(SDL_Surface **dst, t_engine *eng,
				char *name);
void			util_parsing_error_no_sprite(SDL_Surface **dst, t_engine *eng,
				char *name);
int 			util_create_animated_sprite(t_engine *eng, char *str, t_sprite *res);
int 			util_count_frames(t_engine *eng, char *str);
int 			util_create_static_sprite(t_engine *eng, char *str, t_sprite *res);

/*
**	Parsing map functions end
**	---------------------------------------------------------------------------
*/

/*
**	Sprite funs start
**	---------------------------------------------------------------------------
*/

void				sprite_comb_sort(t_sector *sect);
void				sprite_int_swap(int *a, int *b);
void				sprite_float_swap(float *a, float *b);
void				engine_render_sprites_in_sector(t_sector *sect, SDL_Surface *surf, t_player *plr, t_item_sprts *restr);
void				engine_render_sprites(t_engine *eng, t_player *plr, SDL_Surface *surf);
void				check_sprite_pick(t_player *plr, t_sprobject *sobj);
void				apply_sprite_obj(t_player *plr, t_sprobject *sobj);
void				check_sprites_in_sector(t_player *plr, t_sector *sect);
t_bool				modify_players_stat(int *stat, int addtion, int limit);

/*
**	Sprite funs end
**	---------------------------------------------------------------------------
*/


/*
**	Text funs start
**	---------------------------------------------------------------------------
*/

SDL_Surface			*create_text(t_engine *eng, char *str, int color);
void				draw_player_stats(t_engine *eng, SDL_Surface *surf, SDL_Surface *hp, SDL_Surface *armor);
void				engine_render_hud_stats(t_engine *eng, t_player *plr, SDL_Surface *surf);

/*
**	Text funs end
**	---------------------------------------------------------------------------
*/

/*
**
**
*/

float				min(float a, float b);
float				max(float a, float b);
float				clamp(float a, float mi, float ma);
float				vxs(float x0, float y0, float x1, float y1);
short				overlap(float a0, float a1, float b0, float b1);
short				intersect_box(t_point_2d x0, t_point_2d x1, t_point_2d x2, t_point_2d x3);
float				point_side(t_point_2d p, t_point_2d x0, t_point_2d x1);
t_point_2d			intersect(t_point_2d x1, t_point_2d x2, t_point_2d x3, t_point_2d x4);
t_scaler			scaler_init(float data[5]);
/*
**
**
*/
void				engine_render_world_data(t_engine *eng, t_player *plr, t_wall_help2 *data);

void				engine_render_wall_cycle_6(t_wall_clinks *l);
void				engine_render_cycle_5(t_wall_clinks *l);
void				engine_render_wall_cycle_3(t_wall_clinks *l);
void				engine_render_wall_cycle_4(t_wall_clinks *l);
void				engine_render_cycle_2(t_wall_clinks *l);
void				engine_render_cycle_1(t_wall_clinks *l);
void				engine_render_wall_main_cycler(t_wall_clinks *links,
					t_wall_cycle *cycler, t_wall_mai_data *mdata);

void				engine_render_wall_pusher(t_engine *eng,
					t_wall_help2 *data, t_wall_mai_data *mdata);
void				engine_render_particles_wall(t_engine *eng, SDL_Surface *surf,
					t_wall_help2 *data, t_wall_mai_data *mdata);
void				engine_render_world_help(t_engine *eng, t_player *plr,
					SDL_Surface *surf, t_wall_help2 *data);
void				engine_set_links(t_wall_clinks *links, void *ls[6]);

void				eng_reader_prep_data(t_read_data *data, int *stats, char *path);
void				eng_read_sprite_help(t_engine *eng, t_txtr_pkg ***text_buff,
					t_read_data *data, int *stats);
void				sprite_comb_sort_help(t_sorter *data);

void				shoot_help1(t_shoot_data *d, t_engine *eng,
					t_player *plr, int weapon_range);
void				shoot_help2(t_shoot_data *d, t_engine *eng,
					t_player *plr, int weapon_range);
int					shoot_help3(t_shoot_data *d, t_engine *eng,
					t_player *plr, int weapon_range);
int					shoot_help4(t_shoot_data *d, t_engine *eng,
					t_player *plr, int weapon_range);

void				eng_reader_put_data(t_engine *eng, t_read_data *data,
					t_txtr_pkg ***text_buff, void *mass[2]);
void				draw_from_s_to_s_help(t_surf_data *data, SDL_Surface *src);
void				engine_check_object(t_find_obj *d, t_world *world, t_point_3d pos);
void				engine_render_wall_c_val2(t_engine *eng, t_wall_help3 *data_help,
					t_wall_help2 *data, t_wall_mai_data *mdata);
void				engine_render_wall_c_val3(t_engine *eng, t_wall_help3 *data_help,
					t_wall_help2 *data, t_wall_mai_data *mdata);

void				point_swapper_shoot(float *t0, float *t1, float a, float b);

# endif
