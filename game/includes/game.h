/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:26:02 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/08 22:34:12 by zytrams          ###   ########.fr       */
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
# define EyeHeight  6 // Camera height from floor when standing
# define DuckHeight 2.5 // And when crouching
# include <engine.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <libft.h>

typedef	struct		s_game
{
	t_engine		*eng;
	t_player		player;
	long			g_width;
	long			g_height;
}					t_game;

void				init_player(t_player *player, float x, float y, float angle);
void				draw(t_game *fps);
int					rotate_handler(int key, void *param);

#endif
