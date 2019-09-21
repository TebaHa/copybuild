/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:41:43 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/21 18:33:45 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_sdl_init(t_engine **eng)
{
	*eng = (t_engine *)ft_memalloc(sizeof(t_engine));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error_handler("SDL_Init Error: ", SDL_GetError(), (*eng));
	(*eng)->win = SDL_CreateWindow("doka 2", 800, 400, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if ((*eng)->win == NULL)
		error_handler("SDL_CreateWindow Error: ", SDL_GetError(), (*eng));
	(*eng)->ren = SDL_CreateRenderer((*eng)->win, -1, SDL_RENDERER_SOFTWARE);
	if ((*eng)->ren == NULL)
		error_handler("SDL_CreateRenderer Error: ", SDL_GetError(), (*eng));
	engine_read_textures(eng);
	engine_read_sprites(eng);
}

void		engine_sdl_uninit(t_engine *eng)
{
	SDL_DestroyRenderer(eng->ren);
	SDL_DestroyWindow(eng->win);
	SDL_Quit();
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
	d = opendir(TEXTURE_PACK_PATH);
	i = 0;
	(*eng)->stats.textures_count = 0;
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] != '.')
				count++;
		}
		closedir(d);
	}
	d = opendir(TEXTURE_PACK_PATH);
	if (d)
	{
		(*eng)->texture_buffer = (t_txtr_pkg **)ft_memalloc(sizeof(t_txtr_pkg *) * (count));
		if ((*eng)->texture_buffer == NULL)
			error_handler("malloc error: ", "allocation", (*eng));
		while (i < count)
		{
			if ((dir = readdir(d)) != NULL)
			{
				if (dir->d_name[0] == '.')
					continue;
				buffer_name = ft_strjoin(TEXTURE_PACK_PATH, dir->d_name);
				(*eng)->texture_buffer[real_i] = (t_txtr_pkg *)ft_memalloc(sizeof(t_txtr_pkg));
				(*eng)->texture_buffer[real_i]->filename = ft_strdup(dir->d_name);
				(*eng)->stats.textures_count++;
				if ((*eng)->texture_buffer[real_i] == NULL)
					error_handler("malloc error: ", "allocation", (*eng));
				image_load(&(*eng)->texture_buffer[real_i]->texture, buffer_name);
				printf("%s\n",(*eng)->texture_buffer[real_i]->filename);
				free(buffer_name);
				real_i++;
				i++;
			}
		}
		closedir(d);
	}
}

void		engine_read_sprites(t_engine **eng)
{
	int				i;
	int				real_i;
	DIR				*d;
	struct dirent	*dir;
	int				count;
	char			*buffer_name;

	count = 0;
	real_i = 0;
	d = opendir(TEXTURE_SPRITE_PATH);
	i = 0;
	(*eng)->stats.sprites_count = 0;
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] != '.')
				count++;
		}
		closedir(d);
	}
	d = opendir(TEXTURE_SPRITE_PATH);
	if (d)
	{
		(*eng)->sprites_buffer = (t_txtr_pkg **)ft_memalloc(sizeof(t_txtr_pkg *) * (count));
		if ((*eng)->sprites_buffer == NULL)
			error_handler("malloc error: ", "allocation", (*eng));
		while (i < count)
		{
			if ((dir = readdir(d)) != NULL)
			{
				if (dir->d_name[0] == '.')
					continue;
				buffer_name = ft_strjoin(TEXTURE_SPRITE_PATH, dir->d_name);
				(*eng)->sprites_buffer[real_i] = (t_txtr_pkg *)ft_memalloc(sizeof(t_txtr_pkg));
				(*eng)->sprites_buffer[real_i]->filename = ft_strdup(dir->d_name);
				(*eng)->stats.sprites_count++;
				if ((*eng)->sprites_buffer[real_i] == NULL)
					error_handler("malloc error: ", "allocation", (*eng));
				image_load(&(*eng)->sprites_buffer[real_i]->texture, buffer_name);
				printf("%s\n", (*eng)->sprites_buffer[real_i]->filename);
				free(buffer_name);
				real_i++;
				i++;
			}
		}
		closedir(d);
	}
}
