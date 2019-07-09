/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:19:22 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/09 20:28:13 by zytrams          ###   ########.fr       */
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
# include <SDL2/SDL.h>

/* INIT AND UNINIT ENGINE */
//void			uninitengine(void);

typedef	struct		s_point_2d
{
	float			x;
	float			y;
}					t_point_2d;

typedef	struct		s_point_3d
{
	float			x;
	float			y;
	float			z;
}					t_point_3d;

typedef struct		s_polygone
{
	t_point_3d		*vertices;
	int				vertices_size;
}					t_polygone;

typedef struct		s_object
{
	int				sector;
	t_polygone		*polies_array;
}					t_object;

typedef	struct		s_sector
{
	t_object		*objects_array;
}					t_sector;

typedef	struct		s_world
{
	t_sector		*sectors_array;
}					t_world;

typedef	struct		s_control
{
	int				wasd[4];
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
}					t_control;

typedef	struct		s_player
{
	t_control		controller;
	t_point_3d		position; // current position
	t_point_3d		velocity; // current motion vector
	float			angle; // view angle
	unsigned		cursector; // sectornumber
}					t_player;

typedef struct		s_engine
{
	SDL_Event 		event;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_world			*world;
	short			view_type;
}					t_engine;

void			engine_sdl_init(t_engine **eng);
void			engine_sdl_uninit(t_engine *eng);
void			engine_draw_line(t_engine *eng, t_point_2d a, t_point_2d b, int color);
void			engine_render_frame(t_engine *eng);
void			sdl_clear_window(SDL_Renderer *ren);
void			sdl_put_pixel(SDL_Renderer *ren, int x, int y, int color);
void			error_handler(char *error_type, const char *str_error, t_engine *eng);


void			engine_create_test_world(t_world **world);
t_object		engine_create_obj_wall(int portal, t_point_3d a, t_point_3d b, t_point_3d c, t_point_3d d);

#endif
