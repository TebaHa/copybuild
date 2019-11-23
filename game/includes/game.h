/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:26:02 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/21 23:17:00 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define DOWN_ARROW 125
# define TOP_ARROW 126
# define TWO_DIM_KEY 19
# define THREE_DIM_KEY 20
# define HEAD_MARGIN 25
# define EYE_HEIGHT 6
# define DUCK_HEIGHT 2.5
# define KNEE_HEIGHT 10
# include <engine.h>
# include <editor.h>

typedef enum		e_menu_section
{
	M_NONE = -1,
	M_PLAY,
	M_CONTROLS,
	M_EDITOR,
	M_AUTHOR,
	M_EXIT,
	M_BACK,
	M_SECTIONS_NUM
}					t_menu_section;

typedef enum		e_menu_element_enum
{
	ME_AUTHORS,
	ME_ENDGAME,
	ME_CONTROLS,
	ME_ELEMENTS_NUM
}					t_menu_element_enum;

typedef struct		s_game_logic
{
	int				dz;
	int				duck_shift;
	int				thread_start_index;
	int				thread_end_index;
	int				init;
	float			yaw;
	float			px;
	float			py;
	float			dx;
	float			dy;
	int				sect;
	int				sectprev;
	float			move_vec[2];
	int				pushing;
	float			acceleration;
	int				grav;
	t_fix_point_2d	xy;
}					t_game_logic;

typedef struct		s_menu_button
{
	t_bool			active;
	t_fix_point_2d	position;
	t_sprite		*normal;
	t_sprite		*mouseover;
}					t_menu_button;

typedef struct		s_menu_element
{
	t_bool			active;
	t_fix_point_2d	position;
	t_sprite		*sprite;
}					t_menu_element;

typedef struct		s_menu
{
	t_fix_point_2d	position;
	t_menu_section	mouseover_section;
	t_sprite		*background;
	t_menu_button	*button[M_SECTIONS_NUM];
	t_menu_element	*element[ME_ELEMENTS_NUM];
}					t_menu;

typedef struct		s_controller
{
	t_bool			editor;
	t_bool			menu;
	t_bool			game;
	t_bool			work;
}					t_controller;

typedef	struct		s_game
{
	t_sdl			*editor;
	t_engine		*eng;
	t_menu			*menu;
	t_player		player;
	int				thread_num;
	t_thread_pool	render_thread_pool[THREAD_POOL_SIZE];
	t_game_logic	logic;
	t_controller	work;
}					t_game;

void				game_init_player(t_player *plr);
void				game_quit(t_game *fps);
int					game_thread_wrapper(void *ptr);
void				game_init_threads(t_thread_pool *render_thread_pool,
					int sectors);
void				game_stop_threads(t_thread_pool	*render_thread,
					int thread_count);
void				game_threads_recount(t_game *fps);

void				fire(t_player *plr, int state);
void				fire_anim_change(t_engine *eng, t_player *plr);
void				game_init(t_game *fps, int argc, char **argv);

void				game_movement_check(t_game *fps);
void				game_apply_movement_main(t_game *fps);
void				game_apply_movement_main_count1(t_game *fps);
void				game_apply_movement_main_count2(t_game *fps);

void				game_buttons_control_up_main(t_game *fps);
void				game_buttons_control_down_main(t_game *fps);
void				game_buttons_control_down1(t_game *fps);
void				game_buttons_control_down2(t_game *fps);
void				game_buttons_control_down3(t_game *fps);

void				apply_gravitation(t_game *fps);

int					line_intersection_check(t_line_2d plr_dir,
					t_line_2d wall_dir);
void				count_heights(float *hole_low, float *hole_high,
					t_sector *sector);
int					check_wall_passed(t_engine *eng, t_player *plr,
					t_line_2d plr_dir, int *moving);
void				vector_projection(t_player *plr, t_point_3d v1,
					t_point_3d v2);

void				game_render_menu(t_menu *menu, SDL_Surface *surf);
void				game_menu_main(t_game *fps);
void				game_menu_author(t_game *fps);
void 				game_menu_controls(t_game *fps);
void				game_menu_mainframe(t_game *fps);
void				game_menu_endgame(t_game *fps);
void				game_menu_quit(t_game *fps);
void				parser_game(t_game *fps, int argc, char **argv);
void				game_create_resources_from_file(t_game *fps);
void				eng_create_menu(t_game *fps);
void				eng_create_menu_2(t_game *fps);
void				eng_create_menu_3(t_game *fps);

int					check_button(int x, int y,
					t_fix_point_2d pos_a, t_fix_point_2d pos_b);
void				game_find_button(t_game *fps);
void				run_game(t_game *fps);
void				run_controller(t_game *fps);
void				game_end(t_game *fps);
void				game_render_endframe(t_menu *menu, SDL_Surface *surf);

#endif
