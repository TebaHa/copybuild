/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:19:22 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 20:04:17 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <libft.h>
# include <SDL2/SDL.h>
# include <dirent.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# define WIDTH 1024
# define HEIGHT 768
# define TWODIM 2
# define THREEDIM 3
# define PLAYERSTARTZ 0
# define MAXSECTORS 64
# define MAXBUFF	900000
# define HFOV (1.0 * 0.73f * HEIGHT / WIDTH)
# define VFOV (1.0 * 0.2f)
# define TEXTURE_PACK_PATH		"./game/resources/images/"
# define TEXTURE_SPRITE_PATH	"./game/resources/sprites/"
# define SOUND_PATH				"./game/resources/sounds/"
# define GAME_PATH				"./game/resources/levels/1.lvl"
# define FONT_PATH				"./game/resources/fonts/SEASRN__.ttf"
# define RESOURCES_FOLDER		"game/resources/"
# define RESOURCES_PACK			"game/resources.doom"
# define PARSING_ERROR 40
# define READING_ERROR 41
# define CYCLE_READING_ERROR 42
# define PACKAGE_ERROR 43
# define SOUND_ERROR 44
# define MALLOC_ERROR 45
# define PARSING_ERROR_TEXTURE	"!purple"
# define PARSING_ERROR_SPRITE	"!teal"
# define THREAD_POOL_SIZE	3
# define DELAY 15
# define DEFAULT_SPRITE_DELAY	10
# define FIRERATE 30
# define BACKGROUND_MUSIC_VOLUME	0.2
# define GAME_SOUNDS_VOLUME			0.8
# define MAX_DOORS 10
# define TEXT_TIME 150

typedef enum		e_pack_loudness
{
	MODE_SILENT,
	MODE_LOUD
}					t_pack_loudness;

typedef enum		e_pack_cleaning
{
	MODE_LEAVE,
	MODE_CLEANING
}					t_pack_cleaning;

typedef enum		e_sprite_type
{
	NOT_ANIMATBLE,
	ANIMATBLE
}					t_sprite_type;

typedef enum		e_rotate_type
{
	NON_ROTATABLE,
	ROTATABLE
}					t_rotate_type;

typedef enum		e_player_state
{
	P_IDLE,
	P_FIRE,
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
	int				result;
	int				bop;
	int				fd;
	int				ca;
	int				cache;
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
	PLASMA_GUN,
	PLASMA_AMMO,
	BARREL,
	AFRIT,
	CACODEMON,
	IMP,
	JETPACK,
	KEY_RED,
	KEY_BLUE,
	KEY_YELLOW,
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

typedef enum		e_enm_angle
{
	EA_000,
	EA_045,
	EA_090,
	EA_135,
	EA_180,
	EA_225,
	EA_270,
	EA_315,
	EA_NUM
}					t_enm_angle;

typedef enum		e_button_state
{
	BS_INACTIVE,
	BS_ACTIVE,
	BS_PUSHED,
	BS_STATES_NUM
}					t_button_state;

typedef enum		e_button_type
{
	BT_DOOR,
	BT_FINISH,
	BT_RESET,
	BUTTON_NUM
}					t_button_type;

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
	char			*name;
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

typedef	struct		s_color
{
	int				argb;
	int				alpha;
	float			red;
	float			green;
	float			blue;
}					t_color;

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
	int				tex_scale_koef;
	int				id;
	int				type;
	t_image			*texture;
	int				texture_spread;
}					t_polygone;

typedef struct		s_sprite
{
	int				id;
	char			*name;
	SDL_Surface		**surface;
	t_animtn_state	a_state;
	int				frames_num;
	int				frames_delay;
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
	t_button_type	type;
	t_bool			red;
	t_bool			blue;
	t_bool			yellow;
}					t_wallobj;

typedef struct		s_button
{
	int				id;
	char			*name;
	Mix_Chunk		*use_sound;
	t_sprite		*anmtn[BS_STATES_NUM];
}					t_button;

typedef struct		s_wobj
{
	int				id;
	t_button		*type;
	t_button_type	enum_type;
	int				object_id;
	int				height;
	int				position;
	int				sector_id;
	t_bool			red_key;
	t_bool			blue_key;
	t_bool			yellow_key;
}					t_wobj;

typedef struct		s_enemy
{
	int				id;
	char			*name;
	Mix_Chunk		*death_sound;
	t_rotate_type	rotatable;
	t_sprite		*anmtn[E_STATES_NUM];
	t_sprite		**anmtn_360[E_STATES_NUM];
	t_sprite		*shot;
}					t_enemy;

typedef struct		s_weapon
{
	int				id;
	char			*name;
	int				ammo;
	int				max_ammo;
	int				containers;
	int				cooldown;
	t_wpn_state		state;
	t_sprite		*anmtn[W_STATES_NUM];
	t_sprite		*bullet_hole;
	Mix_Chunk		*shot_sound;
	struct s_weapon	*next;
	struct s_weapon	*prev;
}					t_weapon;

typedef struct		s_hud
{
	t_emo_state		emo_state;
	t_health_state	health_state;
	t_sprite		*health;
	t_sprite		*armor;
	t_sprite		*ammo;
	t_sprite		*key_red;
	t_sprite		*key_blue;
	t_sprite		*key_yellow;
	t_sprite		*face[H_STATES_NUM][F_STATES_NUM];
}					t_hud;

typedef struct		s_sprobject
{
	int				id;
	int				angle;
	t_enemy			*type;
	t_enm_type		enum_type;
	int				frame_num;
	int				sector_id;
	t_point_3d		position;
	t_enm_state		state;
	t_bool			norender;
}					t_sprobject;

typedef struct		s_object
{
	t_polygone		polies_array[1];
	int				portal;
	int				passble;
	int				id;
	int				polies_count;
	int				visible;
	int				status;
	t_wallobj		particles[128];
	int				wallobjects_num;
	t_wallobj		*stuff;
	t_wobj			*wallobjects_array;
	t_image			*floor_wall_texture;
	int				floor_wall_spread;
	t_image			*ceil_wall_texture;
	int				ceil_wall_spread;
}					t_object;

typedef struct		s_door_task
{
	int				id;
	t_bool			closed;
	t_bool			renderable;
	t_bool			inuse;
	int				delta;
	int				range;
	int				real_ceil;
	int				real_floor;
}					t_door_task;

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
	t_color			color;
	t_bool			ceil_visible;
	t_image			*ceil_texture;
	int				ceil_spread;
	t_image			*floor_texture;
	int				floor_spread;
	t_item_sprts	item_sprts;
	t_door_task		opening;
}					t_sector;

typedef struct		s_buff
{
	t_point_3d		*vertexes;
	t_sprite		*sprites;
	t_object		*objects;
	t_sprobject		*sprobjects;
	t_wobj			*wallobjects;
	t_sector		*sectors;
	char			**str;
}					t_buff;

typedef struct		s_twall_item
{
	t_item_sprts	*sx;
	t_object		*obj;
	t_color			color;
}					t_twall_item;

typedef struct		s_trns_item
{
	int				status;
	t_item_sprts	*sprite_renderstack;
	t_twall_item	trnsprtstack;
}					t_trns_item;

typedef struct		s_render_stacks
{
	t_item			*renderstack;
	t_trns_item		helpstack[MAXSECTORS * 2];
	char			*rendered;
}					t_render_stacks;

typedef	struct		s_world
{
	t_sector		*sectors_array;
	t_sector		*world_box;
	int				sectors_count;
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

typedef struct		s_sprts_size
{
	float			size_x;
	float			size_y;
	float			s_height;
}					t_sprts_size;

typedef	struct		s_player
{
	t_control		controller;
	t_point_3d		position;
	t_point_3d		velocity;
	t_point_3d		real_position;
	t_weapon		*wpn;
	float			angle;
	float			cosangle;
	float			sinangle;
	float			yaw;
	unsigned		cursector;
	int				firetime;
	int				shoot;
	int				anim;
	int				delay;
	int				frame_num;
	Mix_Chunk		*steps_sound;
	t_player_state	plr_state;
	int				health;
	int				armor;
	int				start_sector;
	t_bool			key_red;
	t_bool			key_blue;
	t_bool			key_yellow;
	t_sprts_size	**arr_sizes;
	t_sprobject		*aim;
	t_bool			grav;
	char			*costil;
	int				text_time;
}					t_player;

typedef struct		s_stats
{
	int				worlds_count;
	int				vertexes_count;
	int				objects_count;
	int				sprobjects_count;
	int				wallobjects_count;
	int				sectors_count;
	int				textures_count;
	int				skins_count;
	int				sprites_count;
	int				players_count;
	int				cycle_detector;
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
	SDL_Event		event;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_world			*world;
	short			view_type;
	t_stats			stats;
	int				*z_buff;
	t_weapon		*weapon[WEAPON_NUM];
	t_enemy			*enemy[ENEMY_NUM];
	t_button		*button[BUTTON_NUM];
	t_hud			*hud;
	t_txtr_pkg		**texture_buffer;
	t_txtr_pkg		**sprites_buffer;
	SDL_Surface		*sky;
	t_sprobject		*tmp;
	TTF_Font		*font;
	Mix_Chunk		*background_music;
	char			*map_name;
	t_door_task		*doors[MAX_DOORS];
	t_sprobject		*aim;
	char			*str_info;
	int				text_time;
	t_bool			ending;
	t_bool			grav;
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
	SDL_Surface		*surface;
	int				value;
	t_render_stacks	ren_stacks;
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
	float			koef;
	t_player		*plr;
	int				ytop[WIDTH];
	int				ybottom[WIDTH];
	int				*tytop;
	int				*tybottom;
	int				portal;
	t_item			sect;
	int				obj_id;
	char			*rendered;
	int				prev;
	t_color			color;
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
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
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
	int				*start;
	int				*end;
}					t_vline1;

typedef struct		s_vline1_in
{
	t_fix_point_3d	a;
	t_fix_point_3d	b;
	t_color			color;
	int				txtx;
}					t_vline1_in;

typedef struct		s_ptcl_h
{
	t_object		*obj;
	t_player		*plr;
	t_item			sect;
}					t_ptcl_h;

typedef struct		s_ptcl_r
{
	t_point_2d		t1;
	t_point_2d		t2;
	t_point_2d		c1;
	t_point_2d		c2;
	int				u0;
	int				u1;
	int				x1;
	int				x2;
	int				y1a;
	int				y2a;
	int				y1b;
	int				y2b;
	int				beginx;
	int				endx;
	float			nearz;
	float			farz;
	float			nearside;
	float			farside;
	float			xscale1;
	float			yscale1;
	float			xscale2;
	float			yscale2;
	float			yceil;
	float			yfloor;
	t_scaler		ya_int;
	t_scaler		yb_int;
	t_object		*obj;
	t_player		*plr;
	t_item			sect;
	t_point_2d		i1;
	t_point_2d		i2;
	t_point_2d		org1;
	t_point_2d		org2;
	int				x;
	int				ya;
	int				yb;
	int				cya;
	int				cyb;
	int				txtx;
}					t_ptcl_r;

typedef struct		s_sprt_r
{
	t_sprite		*img;
	int				i;
	int				j;
	float			planex;
	float			planey;
	float			dirx;
	float			diry;
	float			scaledx;
	float			scaledy;
	float			spritex;
	float			spritey;
	float			stry;
	float			endy;
	float			x1;
	float			x2;
	float			ceil;
	float			floor;
	int				ya;
	int				yb;
	int				begx;
	int				endx;
	int				x;
	int				cya;
	int				cyb;
	int				txtx;
	t_sprobject		*aimed;
}					t_sprt_r;

typedef struct		s_line_2d
{
	t_point_2d		a;
	t_point_2d		b;
}					t_line_2d;

typedef struct		s_surf_and_plr
{
	t_player		*plr;
	SDL_Surface		*surf;
}					t_surf_and_plr;

typedef struct		s_bg
{
	int				x;
	int				y;
	int				sx;
	int				sy;
	int				oy;
	int				*spix;
	int				*dpix;
	int				red;
	int				green;
	int				blue;
}					t_bg;

void				engine_sdl_init(t_engine **eng);
void				engine_sdl_uninit(t_engine *eng);
void				engine_draw_line(t_engine *eng, t_point_2d a,
					t_point_2d b, int color);
void				engine_render_object(t_engine *eng,
					t_object obj, t_player *plr);
void				engine_render_frame(t_engine *eng,
					SDL_Surface *surf);
void				engine_render_world(t_engine *eng, t_player plr,
					SDL_Surface *surf, t_render_stacks *stacks);
void				sdl_clear_window(SDL_Surface *surf);
void				sdl_put_pixel(SDL_Surface *surf,
					int x, int y, int color);
void				error_handler(char *error_type,
					const char *str_error,
					t_engine *eng);
void				engine_create_test_world(t_world **world);
void				engine_push_renderstack(t_item *renderqueue,
					t_item item);
void				engine_clear_renderstack(t_item *renderqueue);
void				engine_create_renderstack(t_engine *eng,
					int render_id, int *rendered);
t_item				engine_pop_renderstack(t_item *renderqueue);
int					engine_object_get_sector(t_world *world,
					t_point_3d pos, int start_sect);
t_object			engine_create_obj_wall(int portal, t_point_3d a,
					t_point_3d b, t_point_3d c, t_point_3d d);
t_point_3d			engine_count_perspective(t_point_3d a, int c);
void				util_release_sectors_buffer(
					t_sector *sector_buff, int size);
void				util_release_objects_buffer(
					t_object *object_buff, int size);
void				util_release_polies_buffer(
					t_polygone *polies_buff, int size);
void				util_release_vertex_buffer(t_point_3d *vertex_buff);
void				util_release_world(t_world *world);
void				util_find_repeats_in_world(t_world *world);
void				engine_present_and_clear_frame(t_engine *eng);
int					intersect_sect(t_point_2d a, t_point_2d b,
					t_point_2d pos);

void				eng_read_sprite(t_engine *eng,
					t_txtr_pkg ***text_buff, int *stats, char *path);
void				engine_triangle(t_engine *eng,
					t_player *plr, t_polygone *t);
int					engine_init_triangle(t_polygone *t, t_tric *trg);
void				engine_do_draw(t_engine *eng,
					t_player *plr, t_tric *trg, int color);
void				engine_do_calc(t_tric *trg);
void				engine_render_wall(t_engine *eng, SDL_Surface *surf,
					t_wall_help2 *data, t_render_stacks *stacks);
void				point_swap_3(t_fix_point_3d *t0, t_fix_point_3d *t1);
void				point_swap_2(t_fix_point_2d *t0, t_fix_point_2d *t1);
int					get_rgb(int r, int g, int b, int a);
float				edge_function(t_point_3d *a,
					t_point_3d *b, t_point_3d *c);
void				zbuffer_zero(int *zbuffer);

float				percent(int start, int end, int current);
int					get_light(int start, int end, float percentage);
int					get_color(int current, int start,
					int end, int colors[2]);

void				engine_render_wall_recount_intersect(t_polygone *polygone,
					t_point_2d *t1, t_point_2d *t2, int *u[2]);
void				engine_render_wall_recount_intersect_help(
					t_wall_help1 *data,
					t_point_2d *t1, t_point_2d *t2);
void				*engine_render_wall_count_values(t_engine *eng,
					t_wall_help3 *data_help,
					t_wall_help2 *data, t_wall_mai_data *mdata);

void				swapper(t_point_3d *a, t_point_3d *b, int *steep);
t_bcontex			bresenham_init(t_point_3d *beg, t_point_3d *end);
t_bcontex			bresenham_init(t_point_3d *beg, t_point_3d *end);
void				bresenham_put_pixel(t_bcontex *c, SDL_Surface *surf,
					int color);
void				bresenham_line(t_point_3d *beg, t_point_3d *end,
							SDL_Surface *surf, int color);
void				triangle_lines(t_polygone *t, SDL_Surface *surf);
void				engine_rasterize_triangle(t_engine *eng,
					t_player *plr, t_polygone *t);
void				ft_swap(float *a, float *b);
t_point_3d			engine_barycentric(t_fix_point_2d pts[3],
					t_fix_point_2d *p);
t_point_3d			engine_cross(t_point_3d a, t_point_3d b);

t_point_3d			cross_vec3(t_point_3d v1, t_point_3d v2);
t_point_3d			create_vector(t_point_3d *a, t_point_3d *b);
double				magnitude(t_point_3d *normal);
void				normalize_vec3(t_point_3d *normal);
t_point_3d			calc_normal(t_polygone *poly);
void				engine_bw_procedural_texture(t_engine *eng,
					t_fix_point_3d a);
double				engine_gain(double gain, int t);
double				engine_bias(double b, int t);
void				engine_render_polygone(t_engine *eng, t_player *plr,
					t_polygone *wall, int *ytop, int *ybottom);
void				engine_vline(t_engine *eng, SDL_Surface *surf,
					t_fix_point_3d a,
					t_fix_point_3d b, int color);
void				engine_render_world_walls(t_engine *eng,
					t_polygone *polygone,
					t_player *plr, t_item sect);
void				engine_render_world_box(t_engine *eng, t_player *plr);
t_point_3d			calc_normal_dots(t_point_3d a, t_point_3d b, t_point_3d c);
void				engine_push_particlestack(t_object *obj, t_weapon *wpn,
					void *d[2], t_point_3d particle);
void				engine_push_checkstack(int *checkqueue, int item);
int					engine_pop_checkstack(int *checkqueue);
void				engine_clear_checkstack(int *checkqueue);
int					check_point_inside_box(t_point_3d a, t_object *obj,
					float ceil, float floor);
void				engine_render_particle(t_engine *eng, SDL_Surface *surf,
					t_wallobj *particle, t_ptcl_h links);
void				get_relative_xy(t_engine *eng, t_fix_point_2d *p);
void				animator_render_sprite_object(t_engine *eng,
					SDL_Surface *surf,
					t_player plr, t_sprobject *spr_obj,
					t_item sect, int *zbuff);
t_sprobject			*create_test_sprobj(t_engine *eng);
void				engine_vline_textured_sprite(SDL_Surface *surf,
					t_scaler ty,
					t_vline1_in din, t_sprite *texture);
void				engine_vline_textured_surface(SDL_Surface *surf,
					t_scaler ty,
					t_vline1_in din, SDL_Surface *texture);
void				switch_weapon(t_engine *eng, t_player *plr, int weapon_num);
int					sound_play_thread_wrapper(void *ptr);
void				engine_render_wall_count_initial_point(t_polygone *polygone,
					t_player *plr,
					t_point_2d	*t1, t_point_2d	*t2);
void				engine_push_spriterenderstack(t_item_sprts **renderqueue,
					t_item_sprts *item);
void				engine_clear_spriterenderstack(t_item_sprts **renderqueue);
t_item_sprts		*engine_pop_spriterenderstack(t_item_sprts **renderqueue);
void				one_dim_zbuffers_copy(t_item_sprts *sprt,
					int *ytop, int *ybottom);
short				engine_z_coord_check(t_sector *sector, t_point_3d pos);
/*
**	---------------------------------------------------------------------------
**	Image-processing functions
*/

void				image_load(t_image *img, const char *fname);
void				image_create(t_image *img, int width,
					int height, int channels);
void				image_free(t_image *img);
t_image				load_textures(const char *fname);
int					scaler_next(t_scaler *i);
void				engine_vline_textured(SDL_Surface *surf, t_scaler ty,
					t_vline1_in din, t_image *texture);
void				move_player(t_engine *eng, t_player *plr, t_point_2d dd);
t_costil			relative_map_coordinate_to_absolute(t_player *plr,
					float map_y, float screen_x, float screen_y);
t_costil			ceiling_floor_screen_coordinates_to_map_coordinates(
					t_player *plr,
					float tz, float tx);
void				change_floor(t_engine *eng, int sect, int change);
void				change_ceil(t_engine *eng, int sect, int change);
void				engine_push_checkstack(int *stack, int sect);
int					engine_pop_checkstack(int *stack);
void				engine_clear_checkstack(int *stack);
t_image				*engine_cut_texture(t_image *world_texture,
					int xstart, int xsize, int ystart, int ysize);
void				game_stop_threads(t_thread_pool
					*render_thread, int thread_count);
void				engine_draw_hud(t_hud *hud, t_player *plr,
					SDL_Surface *surf);
void				shoot(t_engine *eng, t_player *plr, int weapon_range);
int					intersect_3d_seg_plane(t_line s,
					t_plane pn, t_point_3d *res);
void				draw_from_surface_to_surface(SDL_Surface *dest,
					SDL_Surface *src, int dx, int dy);

/*
**	---------------------------------------------------------------------------
**	Checksum functions start
*/

uint_least32_t		crc_calculate(char *buf, size_t len);
int					checksum_check(char *buf, char **buff_splited,
					size_t len);
int					checksum_check_line(char *buff, char *buff_splited,
					int *crc_count, int crc_pos);
void				util_parsing_error_wrong_crc(void);

/*
**	Checksum functions end
**	===========================================================================
**	Resources parsing functions start
*/

void				engine_pack_resources(int loudness, int cleaning);
void				engine_unpack_resources(int loudness, int cleaning);
void				engine_remove_resources_folder(int loudness);
void				engine_remove_resources_pack(int loudness);

void				engine_create_engine_resources(t_engine *eng);

void				eng_create_hud(t_engine *eng);
void				eng_create_face_100_60(t_engine *eng, t_hud *hud);
void				eng_create_face_40_0(t_engine *eng, t_hud *hud);

void				eng_create_weapons(t_engine *eng);
void				eng_create_rifle(t_engine *eng);
void				eng_create_rifle_2(t_engine *eng, t_weapon *rifle);
void				eng_create_plasma(t_engine *eng);
void				eng_create_plasma_2(t_engine *eng, t_weapon *plasma);

void				eng_create_items(t_engine *eng);
void				eng_create_medkit(t_engine *eng);
void				eng_create_armor(t_engine *eng);
void				eng_create_powerup(t_engine *eng);
void				eng_create_jetpack(t_engine *eng);
void				eng_create_rifle_ammo(t_engine *eng);
void				eng_create_plasma_ammo(t_engine *eng);
void				eng_create_plasma_gun(t_engine *eng);
void				eng_create_key_red(t_engine *eng);
void				eng_create_key_blue(t_engine *eng);
void				eng_create_key_yellow(t_engine *eng);

void				eng_create_enemies(t_engine *eng);
void				eng_create_barrel(t_engine *eng);
void				eng_create_afrit(t_engine *eng);
void				eng_create_cacodemon(t_engine *eng);
void				eng_create_imp(t_engine *eng);

void				eng_create_buttons(t_engine *eng);
void				eng_create_button_door(t_engine *eng);
void				eng_create_button_finish(t_engine *eng);
void				eng_create_button_reset(t_engine *eng);

char				*util_add_png_to_name(char *old_name);
char				*util_add_png_num_to_name(char *old_name, int num);
t_sprite			*util_create_sprite_by_name(t_engine *eng, char *str);
t_sprite			*util_create_sprite_by_name_suffix(t_engine *eng,
					char *name, char *suffix);
t_sprite			**util_create_sprite_360_by_name(t_engine *eng, char *str);
t_sprite			**util_create_sprite_0_by_name(t_engine *eng, char *str);

void				sound_mixer_init(void);
Mix_Chunk			*sound_init(char *name);
char				*util_add_wav_to_name(char *old_name);
void				sound_play(Mix_Chunk *sound_name, t_sound_ch channel);
void				sound_shoot(t_player *plr);
void				sound_player_control(t_player *plr);
void				eng_create_background_music(t_engine *eng);

void				infinite_loop(void);

/*
**	Resources parsing functions end
**	===========================================================================
**	Parsing map functions
*/

void				parser_engine(t_engine *eng, t_player *plr);
void				parser_filename(t_engine *eng, int argc, char **argv);
void				engine_preparser(t_engine *eng, char **json_splited);
void				engine_count_all_from_file(t_stats *stats, char **buff);
char				**engine_read_level_file(char *filename);

void				util_release_char_matrix(char **mtrx);
void				util_release_read_buffers(t_buff *buff);

float				util_float10_data_filler(char *str, int min,
					int max);
int					util_int10_data_filler(char *str, int min, int max);
int					util_int16_data_filler(char *str);
void				util_parsing_error_count_handler(char *problem_from,
					char **str, int problems_number);
void				util_parsing_error_cant_find(char *problem, int id_problem);
void				util_parsing_error_lost_handler(char *problem,
					int id_problem,
					char *problem_from, int id_problem_from);
void				util_parsing_error_no_lvl_file(char *problem);
void				util_parsing_error_extra_data(char *problem,
					char *problem_from, char **str);
void				util_parsing_error_little_data(char *problem,
					char *problem_from, char **str);
void				util_parsing_error_not_digit(char *problem);
void				util_parsing_error_not_hex(char *problem);
void				util_parsing_error_not_enough(char *problem);
void				util_parsing_error_lot_of(char *problem);
void				util_parsing_error_repeats(char *problem,
					char *problem_from, int id_problem);
void				util_parsing_error_little_data_check(char *problem_from,
					char **str, int problems_number);
void				util_parsing_value_out_of_limits(char *str);
void				util_parsing_error_double_portal(int sect_1, int sect_2);
void				util_malloc_error(char *str);
void				util_parsing_error_no_cap(char *problem, t_engine *eng);
SDL_Surface			*util_transform_texture_to_sprite(t_image *texture);
SDL_Surface			*util_create_rgb_surface(Uint32 flags, int width,
					int height, int depth);

void				engine_read_plr_pos(t_engine *engine,
					t_player *plr, t_buff buff);
void				engine_read_plr_pos_from_file(t_engine *eng,
					t_player *plr, t_buff buff);
void				util_create_player(t_engine *eng, t_player *plr,
					t_buff buff, char **str);
void				engine_check_plr_pos(t_world *world, t_player *plr);
void				engine_check_plr_vertical_pos(t_world *world,
					t_player *plr);
void				util_parsing_error_player_outside(char *position);

void				engine_read_world_from_file(t_engine *eng,
					t_buff buff);
void				engine_create_world_from_file(t_engine *eng,
					t_player *plr, char *filename);
t_sector			*util_get_sector_from_buff_by_id(int id, int size,
					t_sector *sector, int world_id);
void				util_create_world(t_engine *eng, t_world **world,
					t_buff buff, char **str);

t_point_3d			*engine_read_vertexes_from_file(t_engine *eng,
					char **json_splited);
void				util_create_point_3d(t_engine *eng,
					t_point_3d *point, char **str);
t_point_3d			util_get_vertex_from_buff_by_id(int id, int size,
					t_point_3d *vertexes, int polygone_id);
void				util_find_repeats_in_vertexes(t_point_3d *vertex,
					int vertexes_count);

t_object			*engine_read_objects_from_file(t_engine *eng, t_buff *buff);
void				util_create_object(t_engine *eng, t_object *object,
					t_buff *buff, char **str);
void				util_create_object_2(t_engine *eng, t_object *object,
					t_buff *buff, char **str);
t_object			util_get_object_from_buff_by_id(int id, int size,
					t_object *objects, int sector_id);
void				util_find_repeats_in_objects(t_object *object,
					int objects_count);
void				util_parsing_objects_portal(t_engine *eng, t_buff buff);
void				util_parsing_double_portal(t_engine *eng);
int					util_parsing_double_portal_2(t_engine *eng, int sect_count,
					int obj_count, int obj_count_2);
void				util_fill_object_with_wallobjects(t_engine *eng,
					t_buff *buff, t_object *object);

void				engine_read_sprobjects_from_file(t_engine *eng,
					t_buff *buff);
void				util_create_sprobject(t_engine *eng, t_sprobject
					*sprobject,
					t_buff *buff, char **str);
void				util_fill_sector_with_sprobjects(t_engine *eng,
					t_buff *buff);
void				util_fill_sector_with_sprobjects_2(t_sector *sector,
					t_buff *buff, int *sprobj_count, int *sprobj_count_global);
void				util_fill_sector_with_sprobjects_3(t_engine *eng,
					int sect_count);

t_sector			*engine_read_sectors_from_file(t_engine *eng,
					t_buff buff);
void				engine_read_worldbox_from_file(t_engine *eng,
					t_buff buff);
void				util_create_sector(t_engine *eng, t_buff buff,
					t_sector *sector, char **str);
void				util_create_sector_sprobjs(t_engine *eng,
					t_sector *sector, char **str);
void				util_find_repeats_in_sector(t_sector *sector);
t_sector			*util_get_sector_from_world_by_id(t_engine *eng, int id);
void				util_find_sprobjects_repeats_in_sector(t_sector *sector);

t_wobj				*engine_read_wallobjects_from_file(t_engine *eng,
					t_buff buff);
void				util_create_wallobject(t_engine *eng, t_wobj *wallobject,
					char **str);

void				util_find_texture_by_name(t_image **dst, t_engine *eng,
					char **name, int *spread);
void				util_find_texture_spread(int *spread, char **str);
char				*ft_strcut(char **s, char c);
void				util_parsing_error_no_texture(t_image **dst, t_engine *eng,
					char *name);

void				util_find_sprite_by_name(SDL_Surface **dst, t_engine *eng,
					char *name);
void				util_parsing_error_no_sprite(SDL_Surface
					**dst, t_engine *eng,
					char *name);
int					util_create_animated_sprite(t_engine *eng,
					char *str, t_sprite *res);
int					util_count_frames(t_engine *eng, char *str);
int					util_create_static_sprite(t_engine *eng,
					char *str, t_sprite *res);
void				util_read_color(t_color *color, char *str);
void				close_game(int error);
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
t_sprobject			*engine_render_sprites_in_sector(t_sector *sect,
					SDL_Surface *surf, t_player *plr, t_item_sprts *restr);
void				engine_render_sprites(t_engine *eng, t_player *plr,
					SDL_Surface *surf, t_render_stacks *stacks);
void				check_sprite_pick(t_player *plr, t_sprobject *sobj);
void				apply_sprite_obj(t_player *plr, t_sprobject *sobj);
void				check_sprites_in_sector(t_player *plr, t_sector *sect);
t_bool				modify_players_stat(int *stat, int addtion, int limit);

/*
**	Text funs start
**	---------------------------------------------------------------------------
*/

SDL_Surface			*create_text(t_engine *eng, char *str, int color);
void				draw_player_stats(t_engine *eng, SDL_Surface *txt,
					t_point_2d place);
void				engine_render_hud_stats(t_engine *eng, t_player *plr);

/*
**	Text funs end
**	---------------------------------------------------------------------------
*/

/*
**	Intersection funs
**	---------------------------------------------------------------------------
*/

float				min(float a, float b);
float				max(float a, float b);
float				clamp(float a, float mi, float ma);
float				vxs(float x0, float y0, float x1, float y1);
short				overlap(float a0, float a1, float b0, float b1);
short				intersect_box(t_point_2d x0, t_point_2d x1,
					t_point_2d x2, t_point_2d x3);
float				point_side(t_point_2d p, t_point_2d x0,
					t_point_2d x1);
t_point_2d			intersect(t_point_2d x1, t_point_2d x2,
					t_point_2d x3, t_point_2d x4);
t_scaler			scaler_init(float data[5]);

/*
**	Norm funs
**	---------------------------------------------------------------------------
*/
void				engine_render_world_data(t_player *plr, t_wall_help2 *data);

void				engine_render_wall_cycle_6(t_wall_clinks *l);
int					engine_render_cycle_5(t_wall_clinks *l);
void				engine_render_wall_cycle_3(t_wall_clinks *l);
void				engine_render_wall_cycle_4(t_wall_clinks *l);
void				engine_render_cycle_2(t_wall_clinks *l);
void				engine_render_cycle_1(t_wall_clinks *l);
void				engine_render_wall_main_cycler(t_wall_clinks *links,
					t_wall_cycle *cycler, t_wall_mai_data *mdata);

void				engine_render_wall_pusher(t_engine *eng, t_wall_help2 *data,
					t_wall_mai_data *mdata, t_render_stacks *stacks);
void				engine_render_particles_wall(t_engine *eng,
					SDL_Surface *surf, t_wall_help2 *data);
void				engine_render_world_help(t_engine *eng, SDL_Surface *surf,
					t_wall_help2 *data, t_render_stacks *stacks);
void				engine_set_links(t_wall_clinks *links, void *ls[6]);

void				eng_reader_prep_data(t_read_data *data,
					int *stats, char *path);
void				eng_read_sprite_help(t_engine *eng, t_txtr_pkg ***text_buff,
					t_read_data *data, int *stats);
void				sprite_comb_sort_help(t_sorter *data);

void				shoot_help1(t_shoot_data *d, t_engine *eng,
					t_player *plr, int weapon_range);
void				shoot_help2(t_shoot_data *d);
int					shoot_help3(t_shoot_data *d, t_engine *eng, t_player *plr);
int					shoot_help4(t_shoot_data *d, t_engine *eng, t_player *plr);

void				eng_reader_put_data(t_engine *eng, t_read_data *data,
					t_txtr_pkg ***text_buff, void *mass[2]);
void				draw_from_s_to_s_help(t_surf_data *data, SDL_Surface *src);
void				draw_from_s_to_s_help_1(t_surf_data *data,
					SDL_Surface *src);
void				engine_check_object(t_find_obj *d,
					t_world *world, t_point_3d pos);
void				engine_render_wall_c_val2(t_wall_help3 *data_help,
					t_wall_help2 *data, t_wall_mai_data *mdata);
void				engine_render_wall_c_val3(t_wall_help2 *data,
					t_wall_mai_data *mdata);

void				point_swapper_shoot(float *t0, float *t1, float a, float b);

void				engine_render_particle(t_engine *eng,
					SDL_Surface *surf,
					t_wallobj *particle, t_ptcl_h links);
void				engine_render_particle_1(t_wallobj *particle,
					t_ptcl_r *data);
void				engine_render_particle_2(t_wallobj *particle,
					t_ptcl_r *data);
void				engine_render_particle_3(t_ptcl_r *data);
void				engine_render_particle_4(t_wallobj *particle,
					t_ptcl_r *data);
void				engine_render_particle_5(t_ptcl_r *data);
short				engine_render_particle_6(t_wallobj *particle,
					t_ptcl_r *data);
short				engine_render_particle_7(t_engine *eng,
					SDL_Surface *surf,
					t_wallobj *particle, t_ptcl_r *data);
void				engine_render_particle_links(t_ptcl_r *data,
					t_ptcl_h *links);

void				engine_render_sprites_in_sector_1(t_sector *sect,
					t_player *plr, t_sprt_r *d);
void				engine_render_sprites_in_sector_2(t_sprt_r *d);
short				engine_render_sprites_in_sector_3(t_sector *sect,
					t_player *plr, t_sprt_r *d);
void				engine_render_sprites_in_sector_4(t_sector *sect,
					SDL_Surface *surf, t_sprt_r *d);
int					engine_render_sprites_in_sector_wrap(t_sector *sect,
					t_player *plr, t_sprt_r *d);
void				sort_sprites(t_sector *sect, t_player *plr);
void				initilize_abs_sprt_sizes(t_player *plr);
float				dot_product(t_point_3d a, t_point_3d b);
void				get_sprite_image(t_sector *sect, t_player *plr,
					t_sprt_r *d);
void				get_sprite_anim_obj(int angle_id,
					t_player *plr, t_sprobject *obj, t_sprt_r *d);
void				get_sprite_anim_obj_std(t_player *plr,
					t_sprobject *obj, t_sprt_r *d);
void				get_sprite_rotatable_obj(t_player *plr,
					t_sprobject	*obj, t_sprt_r *d);
int					get_id_by_angle(float angle);

float				dot_product_2d(t_point_2d a, t_point_2d b);
void				normalize_2d(t_point_2d *normal);
float				magnitude_2d(t_point_2d *normal);
void				engine_clear_surface(SDL_Surface *surf);

/*
**	Background functions start
**	---------------------------------------------------------------------------
*/

void				engine_find_background(t_engine *eng);
void				engine_draw_background(t_engine *eng,
					SDL_Surface *surf, float yaw, float plrangle);
/*
**	Background functions end
**	---------------------------------------------------------------------------
*/
int					line_intersection_check(t_line_2d a, t_line_2d b);
void				prepare_polygones(t_engine *eng);

void				wall_objects_init(t_engine *eng);
void				wall_object_init(t_engine *eng, t_object *obj,
					t_wobj *particlestack, t_point_3d particle);

void				use(t_engine *eng, t_player *plr);
int					check_point_inside_wbox(t_point_3d a,
					t_wallobj *obj, float ceil, float floor);

void				engine_run_doors(t_engine *eng, t_door_task **stack);
int					execute_door(t_door_task *door, t_sector *sect);
void				engine_push_doorqueue(t_door_task **stack,
					t_door_task *item);
void				engine_flush_doorqueue(t_door_task **stack);
void				add_task(t_engine *eng, t_sector *sect,
					t_wobj *obj, t_player *plr);
int					close_door(t_door_task *door, t_sector *sect);
int					open_door(t_door_task *door, t_sector *sect);
void				init_sectors(t_engine *eng);
void				kill(t_sprobject *sobj);

void				engine_push_tsrenderstack(t_trns_item *renderqueue,
					t_trns_item item);
void				engine_clear_tsrenderstack(t_trns_item *renderqueue);
t_trns_item			engine_pop_tsrenderstack(t_trns_item *renderqueue);
void				engine_render_twall_main_cycler(t_wall_clinks *l,
					t_wall_cycle *cycler, t_wall_mai_data *mdata);
void				engine_set_tlinks(t_wall_clinks *links, void *ls[6]);
void				engine_render_twall(t_engine *eng, SDL_Surface *surf,
					t_wall_help2 *data, t_render_stacks *stacks);
void				engine_render_twall_c_val3(t_wall_help2 *data,
					t_wall_mai_data *mdata);
void				engine_render_twall_c_val2(t_wall_help3 *data_help,
					t_wall_help2 *data, t_wall_mai_data *mdata);
void				*engine_render_twall_count_values(t_engine *eng,
					t_wall_help3 *data_help, t_wall_help2 *data,
					t_wall_mai_data *mdata);
void				engine_render_twall_count_initial_point(
					t_polygone *polygone, t_player *plr, t_point_2d *t1,
					t_point_2d *t2);
void				engine_redner_twall_recount_prep_data(t_wall_help1 *data,
					t_point_2d *t1, t_point_2d *t2);
void				engine_render_twall_recount_intersect_help(
					t_wall_help1 *data, t_point_2d *t1, t_point_2d *t2);
void				engine_render_twall_recount_intersect(t_polygone *polygone,
					t_point_2d *t1, t_point_2d *t2, int *u[2]);
void				engine_render_twall_cycle(t_wall_clinks *l);
void				engine_render_twalls(t_engine *eng, SDL_Surface *surf,
					t_wall_help2 *data, t_render_stacks *stacks);
void				engine_render_ts_objects(t_engine *eng, t_surf_and_plr ps,
					t_wall_help2 *data, t_render_stacks *stacks);
void				sprt_first_push(t_render_stacks *stacks,
					t_item_sprts *sptrs);
t_bool				apply_sprite_key(t_player *plr, t_sprobject *sobj);

void				engine_replace_text(t_player *plr, char *str);
void				engine_check_text(t_engine *eng);
void				engine_put_text(t_engine *eng, t_player *plr);
void				engine_render_text(t_engine *eng, t_player *plr);
void				engine_render_keys(t_hud *hud, t_sprite *img,
					t_player *plr, SDL_Surface *surf);
void				instant_close_door(t_sector *sect);
void				engine_render_sprites_in_sector_help(t_sector *sect,
					SDL_Surface *surf, t_sprt_r	*d, t_item_sprts *restr);
void				init_portal_data(t_engine *eng, t_wall_help3 *data_help,
					t_wall_help2 *data, t_wall_mai_data *mdata);
void				engine_render_particle_8(t_wallobj *particle,
					t_ptcl_r *data);
void				engine_render_particles_wall_help(t_engine *eng,
					SDL_Surface *surf, t_wall_help2 *data);
void				engine_render_particle_animate(t_wallobj *particle);
void				engine_draw_background_help(t_engine *eng,
					SDL_Surface *surf, t_bg	*bg);
t_bool				apply_sprite_obj_help(t_player *plr, t_sprobject *sobj);
void				prepare_polegone_help(t_sector *s, int j);
void				engine_render_ts_object_help(t_wall_help2 *data,
					t_trns_item item);
void				init_wobj_help(t_object *obj, t_point_3d *particle);
void				init_wobj_help2(t_object *obj, t_wobj *txtr,
					t_point_3d *particle, t_sh_part *data);
void				engine_render_wall_cycle_main_wall(t_wall_clinks *l);

#endif
