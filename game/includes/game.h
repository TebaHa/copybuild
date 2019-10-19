/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:26:02 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/19 19:27:44 by zytrams          ###   ########.fr       */
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
# define HeadMargin 25
# define EyeHeight  6 // Camera height from floor when standing
# define DuckHeight 2.5 // And when crouching
# define KneeHeight 10
# include <engine.h>
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
typedef	struct		s_game
{
	t_engine		*eng;
	t_player		player;
	int				thread_num;
	t_thread_pool	render_thread_pool[THREAD_POOL_SIZE];
	t_game_logic	logic;
}					t_game;

void			game_create_test_player(t_player *plr);
int				game_thread_wrapper(void *ptr);
void			game_init_threads(t_thread_pool *render_thread_pool);
void			game_stop_threads(t_thread_pool	*render_thread,
				int thread_count);
void			game_threads_recount(t_game *fps);

void			fire(t_engine *eng, t_player *plr, int state);
void			fire_anim_change(t_engine *eng, t_player *plr);
void			game_init(t_game *fps);


void			game_movement_check(t_game *fps);
void			game_apply_movement_main(t_game *fps);
void			game_apply_movement_main_count1(t_game *fps);
void			game_apply_movement_main_count2(t_game *fps);

void			game_buttons_control_up_main(t_game *fps);
int				game_buttons_control_down_main(t_game *fps);
void			game_buttons_control_down1(t_game *fps);
void			game_buttons_control_down2(t_game *fps);
void			game_buttons_control_down3(t_game *fps);

void			apply_gravitation(t_game *fps);

#endif
