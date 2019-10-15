/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:41:43 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/15 20:41:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_sdl_init(t_engine **eng)
{
	*eng = (t_engine *)ft_memalloc(sizeof(t_engine));
	if (TTF_Init() != 0)
		error_handler("SDL_Init Error: ", SDL_GetError(), (*eng));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error_handler("SDL_Init Error: ", SDL_GetError(), (*eng));
	(*eng)->win = SDL_CreateWindow("doka 2",
	800, 400, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if ((*eng)->win == NULL)
		error_handler("SDL_CreateWindow Error: ", SDL_GetError(), (*eng));
	(*eng)->ren = SDL_CreateRenderer((*eng)->win, -1, SDL_RENDERER_SOFTWARE);
	if ((*eng)->ren == NULL)
		error_handler("SDL_CreateRenderer Error: ", SDL_GetError(), (*eng));
	sound_mixer_init();
	(*eng)->font = TTF_OpenFont(FONT_PATH, 16);
	if ((*eng)->font == NULL)
		error_handler("SDL_CreateFonts Error: ", SDL_GetError(), (*eng));
}

void		engine_sdl_uninit(t_engine *eng)
{
	TTF_CloseFont(eng->font);
	TTF_Quit();
	SDL_DestroyRenderer(eng->ren);
	SDL_DestroyWindow(eng->win);
	SDL_Quit();
}

void		eng_read_sprite(t_engine *eng, t_txtr_pkg ***text_buff, int *stats, char *path)
{
	t_read_data	data;

	eng_reader_prep_data(&data, stats, path);
	if (data.d)
	{
		text_buff[0] = (t_txtr_pkg **)ft_memalloc(sizeof(t_txtr_pkg *) * (data.count));
		if (text_buff[0] == NULL)
			error_handler("malloc error: ", "allocation", eng);
		while (data.i < data.count)
		{
			if ((data.dir = readdir(data.d)) != NULL)
			{
				if (data.dir->d_name[0] == '.')
					continue;
				data.buffer_name = ft_strjoin(path, data.dir->d_name);
				(text_buff)[0][data.real_i] = (t_txtr_pkg *)ft_memalloc(sizeof(t_txtr_pkg));
				(text_buff)[0][data.real_i]->filename = ft_strdup(data.dir->d_name);
				(*stats)++;
				if ((text_buff)[0][data.real_i] == NULL)
					error_handler("malloc error: ", "allocation", eng);
				image_load(&(text_buff)[0][data.real_i]->texture, data.buffer_name);
				free(data.buffer_name);
				data.real_i++;
				data.i++;
			}
		}
		closedir(data.d);
	}
}

void		eng_reader_prep_data(t_read_data *data, int *stats, char *path)
{
	data->count = 0;
	data->real_i = 0;
	data->d = opendir(path);
	data->i = 0;
	*stats = 0;
	if (data->d)
	{
		while ((data->dir = readdir(data->d)) != NULL)
		{
			if (data->dir->d_name[0] != '.')
				data->count++;
		}
		closedir(data->d);
	}
	data->d = opendir(path);
}
