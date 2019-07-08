/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:19:22 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/08 22:39:07 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# define WIDTH 2000
# define HEIGHT 1200
# define TWODIM 2
# define THREEDIM 3
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <libft.h>
# include <stdio.h>
# include <SDL.h>

/* INIT AND UNINIT ENGINE */
//void			uninitengine(void);

typedef	struct	s_point_2d
{
	float		x;
	float		y;
}				t_point_2d;

typedef	struct	s_point_3d
{
	float		x;
	float		y;
	float		z;
}				t_point_3d;


typedef	struct	s_control
{
	int			wasd[4];
	int			ground;
	int			falling;
	int			moving;
	int			ducking;
}				t_control;

typedef	struct	s_player
{
	t_control	controller;
	t_point_3d	position; // current position
	t_point_3d	velocity; // current motion vector
	float		angle; // view angle
	unsigned	cursector; // sectornumber
}				t_player;

typedef struct	s_engine
{
	short		view_type;
}				t_engine;

#endif
