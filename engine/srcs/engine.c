/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:41:43 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/26 18:24:34 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_sdl_init(t_engine **eng)
{
	DIR *d;
	struct dirent *dir;
	d = opendir("./game/resources/images/");

	*eng = (t_engine *)ft_memalloc(sizeof(t_engine));
	(*eng)->z_buff = (int *)ft_memalloc(sizeof(int) * WIDTH * HEIGHT);
	(*eng)->image_buffer = (t_image **)ft_memalloc(sizeof(t_image *) * 1);
	zbuffer_zero((*eng)->z_buff);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error_handler("SDL_Init Error: ", SDL_GetError(), (*eng));
	(*eng)->win = SDL_CreateWindow("doka 2", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if ((*eng)->win == NULL)
		error_handler("SDL_CreateWindow Error: ", SDL_GetError(), (*eng));
	(*eng)->ren = SDL_CreateRenderer((*eng)->win, -1, SDL_RENDERER_ACCELERATED);
	if ((*eng)->ren == NULL)
		error_handler("SDL_CreateRenderer Error: ", SDL_GetError(), (*eng));
	(*eng)->surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, (Uint32)0xff000000,
							(Uint32)0x00ff0000, (Uint32)0x0000ff00, (Uint32)0x000000ff);
	if ((*eng)->surface == NULL)
		error_handler("SDL_CreateSurface Error: ", SDL_GetError(), (*eng));
	engine_read_textures(eng);
}

void		engine_sdl_uninit(t_engine *eng)
{
	SDL_DestroyRenderer(eng->ren);
	SDL_DestroyWindow(eng->win);
	SDL_Quit();
}

void	zbuffer_zero(int *zbuffer)
{
	int i;

	i = HEIGHT * WIDTH - 1;
	while (i)
	{
		zbuffer[i] = (INT32_MIN);
		i--;
	}
}

void		engine_read_textures(t_engine **eng)
{
	int				i;
	int				real_i;
	DIR				*d;
	struct dirent	*dir;
	int				count;
	char			*buffer_name;

	count = 0;
	real_i = 0;
	d = opendir("./game/resources/images/");
	i = 0;
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			count++;
		closedir(d);
	}
	d = opendir("./game/resources/images/");
	if (d)
	{
		(*eng)->image_buffer = (t_image **)ft_memalloc(sizeof(t_image *) * (count - 2));
		if ((*eng)->image_buffer == NULL)
			error_handler("malloc error: ", "allocation", (*eng));
		while (i < 2)
		{
			dir = readdir(d);
			i++;
		}
		while (i < count)
		{
			if ((dir = readdir(d)) != NULL)
			{
				buffer_name = ft_strjoin("./game/resources/images/", dir->d_name);
				(*eng)->image_buffer[real_i] = (t_image *)ft_memalloc(sizeof(t_image));
				if ((*eng)->image_buffer[real_i] == NULL)
					error_handler("malloc error: ", "allocation", (*eng));
				image_load((*eng)->image_buffer[real_i], buffer_name);
				free(buffer_name);
				real_i++;
				i++;
			}
		}
		closedir(d);
	}
}
