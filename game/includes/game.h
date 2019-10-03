/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:26:02 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/03 06:10:51 by zytrams          ###   ########.fr       */
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

typedef	struct		s_game
{
	t_engine		*eng;
	t_player		player;
	int				thread_num;
	t_thread_pool	render_thread_pool[THREAD_POOL_SIZE];
}					t_game;

void			game_create_test_player(t_player *plr);
static	int		game_thread_wrapper(void *ptr);
void			fire(t_engine *eng, t_player *plr, int state);
void			fire_anim_change(t_engine *eng, t_player *plr);

#endif
