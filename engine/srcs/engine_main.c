/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:41:43 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/22 19:52:04 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_sdl_init(t_engine **eng)
{
	 engine_unpack_resources(MODE_SILENT, MODE_LEAVE);
	if ((*eng = (t_engine *)ft_memalloc(sizeof(t_engine))) == NULL)
		util_malloc_error("eng");
	if (TTF_Init() != 0)
		error_handler("SDL_Init Error: ", SDL_GetError(), (*eng));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error_handler("SDL_Init Error: ", SDL_GetError(), (*eng));
	(*eng)->win = SDL_CreateWindow("doka 2",
	800, 400, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if ((*eng)->win == NULL)
		error_handler("SDL_CreateWindow Error: ", SDL_GetError(), (*eng));
	(*eng)->ren = SDL_CreateRenderer((*eng)->win, -1, SDL_RENDERER_ACCELERATED);
	if ((*eng)->ren == NULL)
		error_handler("SDL_CreateRenderer Error: ", SDL_GetError(), (*eng));
	sound_mixer_init();
	(*eng)->font = TTF_OpenFont(FONT_PATH, 16);
	if ((*eng)->font == NULL)
		error_handler("SDL_CreateFonts Error: ", SDL_GetError(), (*eng));
	(*eng)->str_info = NULL;
}

void		engine_sdl_uninit(t_engine *eng)
{
	TTF_CloseFont(eng->font);
	TTF_Quit();
	SDL_DestroyRenderer(eng->ren);
	SDL_DestroyWindow(eng->win);
	SDL_Quit();
}

void		eng_read_sprite(t_engine *eng,
			t_txtr_pkg ***text_buff, int *stats, char *path)
{
	t_read_data	data;

	eng_reader_prep_data(&data, stats, path);
	if (data.d)
	{
		if ((*text_buff = (t_txtr_pkg **)
		ft_memalloc(sizeof(t_txtr_pkg *) * (data.count))) == NULL)
			util_malloc_error("text_buff");
		while (data.i < data.count)
		{
			if ((data.dir = readdir(data.d)) != NULL)
			{
				if (data.dir->d_name[0] == '.')
					continue;
				eng_reader_put_data(eng,
				&data, text_buff, (void *[2]){path, stats});
			}
		}
		closedir(data.d);
	}
}

void		eng_reader_put_data(t_engine *eng, t_read_data *data,
			t_txtr_pkg ***text_buff, void *mass[2])
{
	char	*path;
	int		*stats;

	path = (char *)mass[0];
	stats = (int *)mass[1];
	data->buffer_name = ft_strjoin(path, data->dir->d_name);
	if (((*text_buff)[data->real_i] =
	(t_txtr_pkg *)ft_memalloc(sizeof(t_txtr_pkg))) == NULL)
		util_malloc_error("real_i");
	(*text_buff)[data->real_i]->filename = ft_strdup(data->dir->d_name);
	(*stats)++;
	if ((*text_buff)[data->real_i] == NULL)
		error_handler("malloc error: ", "allocation", eng);
	image_load(&(*text_buff)[data->real_i]->texture, data->buffer_name);
	free(data->buffer_name);
	data->real_i++;
	data->i++;
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
