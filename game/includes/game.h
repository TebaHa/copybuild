/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:26:02 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/05 19:38:28 by zytrams          ###   ########.fr       */
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

typedef enum		e_menu_section
{
	M_NONE = -1,
	M_STORY,
	M_LOAD_MAP,
	M_EDITOR,
	M_AUTHOR,
	M_EXIT,
	M_SECTIONS_NUM
}					t_menu_section;

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
	t_fix_point_2d	position;
	t_sprite		*normal;
	t_sprite		*active;
}					t_menu_button;

typedef struct		s_menu
{
	t_fix_point_2d	position;
	t_menu_section	active_section;
	t_sprite		*background;
	t_menu_button	*button[M_SECTIONS_NUM];
}					t_menu;

typedef	struct		s_game
{
	t_engine		*eng;
	t_menu			*menu;
	t_player		player;
	int				thread_num;
	t_thread_pool	render_thread_pool[THREAD_POOL_SIZE];
	t_game_logic	logic;
}					t_game;

void				game_init_player(t_player *plr);
void				game_quit(t_game *fps);
int					game_thread_wrapper(void *ptr);
void				game_init_threads(t_thread_pool *render_thread_pool);
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

int					line_intersection_check(t_line_2d plr_dir, t_line_2d wall_dir);
void				count_heights(float *hole_low, float *hole_high,
					t_sector *sector);
int					check_wall_passed(t_engine *eng, t_player *plr,
					t_line_2d plr_dir, int *moving);
void				vector_projection(t_player *plr, t_point_3d v1, t_point_3d v2);

void				game_render_menu(t_menu *menu, SDL_Surface *surf);
void				game_menu_main(t_game *fps);
void				game_menu_quit(t_game *fps);
void				parser_game(t_game *fps, int argc, char **argv);
void				game_create_resources_from_file(t_game *fps);
void				eng_create_menu(t_game *fps);

int					check_button(int x, int y,
					t_fix_point_2d pos_a, t_fix_point_2d pos_b);
void				game_find_button(t_game *fps);
void				run_game(t_game *fps);

#endif
