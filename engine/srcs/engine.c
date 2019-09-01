/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:41:43 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/01 19:27:26 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_sdl_init(t_engine **eng)
{
	*eng = (t_engine *)ft_memalloc(sizeof(t_engine));
	(*eng)->z_buff = (int *)ft_memalloc(sizeof(int) * WIDTH * HEIGHT);
	zbuffer_zero((*eng)->z_buff);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error_handler("SDL_Init Error: ", SDL_GetError(), (*eng));
	(*eng)->win = SDL_CreateWindow("doka 2", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if ((*eng)->win == NULL)
		error_handler("SDL_CreateWindow Error: ", SDL_GetError(), (*eng));
	(*eng)->ren = SDL_CreateRenderer((*eng)->win, -1, SDL_RENDERER_SOFTWARE);
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
	(*eng)->stats.textures_count = 0;
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			count++;
		closedir(d);
	}
	d = opendir("./game/resources/images/");
	if (d)
	{
		(*eng)->texture_buffer = (t_txtr_pkg **)ft_memalloc(sizeof(t_txtr_pkg *) * (count - 2));
		if ((*eng)->texture_buffer == NULL)
			error_handler("malloc error: ", "allocation", (*eng));
		while (i < 2)
		{
			i++;
		}
		while (i < count)
		{
			if ((dir = readdir(d)) != NULL)
			{
				buffer_name = ft_strjoin("./game/resources/images/", dir->d_name);
				(*eng)->texture_buffer[real_i] = (t_txtr_pkg *)ft_memalloc(sizeof(t_txtr_pkg));
				(*eng)->texture_buffer[real_i]->filename = ft_strdup(dir->d_name);
				(*eng)->stats.textures_count++;
				if ((*eng)->texture_buffer[real_i] == NULL)
					error_handler("malloc error: ", "allocation", (*eng));
				image_load(&(*eng)->texture_buffer[real_i]->texture, buffer_name);
				free(buffer_name);
				real_i++;
				i++;
			}
		}
		closedir(d);
	}
}
