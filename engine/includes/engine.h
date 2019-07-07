/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:19:22 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/07 20:29:20 by zytrams          ###   ########.fr       */
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
# include <mlx.h>
# include <stdio.h>

/* INIT AND UNINIT ENGINE */
//void			uninitengine(void);

/* BSP ARRAYS */
typedef	struct	s_point
{
	int		x;
	int		y;
	int		z;
}				t_point;

typedef struct	s_wall_pos
{
	t_point		a;
	t_point		b;
}				t_wall_pos;

typedef	struct	s_sector
{
	long		id;
	long		start_wall;
	long		walls_count;
}				t_sector;

typedef	struct	s_wall
{
	long		id;
	t_wall_pos	pos;
	long		next_sector;
}				t_wall;

typedef	struct	s_portals
{
	t_wall		*wall_array;
	long		wall_count;
	t_sector	*sector_array;
	long		sector_count;
}				t_portals;

typedef struct	s_mxl_win
{
	void		*ptr_mlx;
	void		*ptr_window;
	long		width;
	long		height;
}				t_mxl_win;

typedef struct	s_image
{
	void		*ptr_img;
	void		*ptr_data;
	int			bpp;
	int			size_line;
	int			endian;
	long		width;
	long		height;
}				t_image;

typedef	struct	s_player
{
	long		px;
	long		py;
	double		angle;
}				t_player;

typedef struct	s_engine
{
	t_portals	portals;
	t_image		img;
	t_mxl_win	window;
	short		view_type;
}				t_engine;


//void			createsectors(char *filename);


/* get current sector */
//void			updatesector(int x, int y, int *last_known_id);
/*  */

t_engine		*init_engine(void);
void			init_image(void *mlx, t_image *img, int width, int height);
void			init_window(t_mxl_win *window);
void			create_portal_map(t_portals *lvl);
void			create_sector(long id, t_sector *sector, long size, long start);
void			create_wall(long id, t_wall *array, t_point a, t_point b, long portal);
void			draw_map_2d(t_image *image, t_portals *lvl, t_player *plr);
void			draw_player_2d(t_image *image, int x, int y, double angle);

void			draw_map_3d(t_image *image, t_portals *lvl, t_player *plr);

void			draw_line(t_image *image, t_point a, t_point b, int color);
void			put_on_image(int x, int y, int color, t_image *image);

long			dot_cross(t_point a, t_point b);
t_point			intersect(t_point a, t_point b, t_point c, t_point d);

#endif
