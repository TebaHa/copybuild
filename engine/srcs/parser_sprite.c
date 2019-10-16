/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_sprite	*engine_read_sprites_from_file(t_engine *eng,
			t_buff buff)
{
	t_sprite	*sprites_buff;
	char		**splitted_line;
	int			i;

	sprites_buff = (t_sprite *)ft_memalloc(sizeof(t_sprite) *
										   eng->stats.skins_count);
	i = 0;
	eng->stats.skins_count = 0;
	while (buff.str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
		if (ft_strcmp(splitted_line[0], "sprite:") == 0)
			util_create_sprite(eng, &sprites_buff[eng->stats.skins_count],
							   splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (sprites_buff);
}

void	util_parsing_error_no_sprite(SDL_Surface **dst, t_engine *eng,
									 char *name)
{
	util_parsing_error_no_cap("sprite", eng);
	ft_putendl("Parsing error:");
	ft_putstr("Cant find sprite: ");
	ft_putstr(name);
	ft_putstr("!\n");
	util_find_sprite_by_name(dst, eng, PARSING_ERROR_SPRITE);
	if (!ft_strcmp(name, PARSING_ERROR_SPRITE))
		exit(PARSING_ERROR);
}

t_sprite	*util_create_sprite_by_name(t_engine *eng, char *str)
{
	t_sprite *res;

	res = (t_sprite *) ft_memalloc(sizeof(t_sprite));
	res->surface = (SDL_Surface **) ft_memalloc(sizeof(SDL_Surface));
	res->frames_delay = DEFAULT_SPRITE_DELAY;
	if (util_create_static_sprite(eng, str, res))
		return (res);
	else if (util_create_animated_sprite(eng, str, res))
		return (res);
	res->frames_num = 1;
	res->a_state = STATIC;
	util_parsing_error_no_sprite(res->surface, eng, str);
	res->name = util_add_png_to_name(PARSING_ERROR_SPRITE);
	return (res);
}

int 		util_create_static_sprite(t_engine *eng, char *str, t_sprite *res)
{
	int i;

	i = 0;
	res->name = util_add_png_to_name(str);
	while (i < eng->stats.sprites_count)
	{
		if (!ft_strcmp(res->name, eng->sprites_buffer[i]->filename))
		{
			res->frames_num = 1;
			res->a_state = STATIC;
			res->surface = (SDL_Surface **) ft_memalloc(sizeof(SDL_Surface *));
			res->surface[0] = util_transform_texture_to_sprite(
					&eng->sprites_buffer[i]->texture);
			break;
		}
		i++;
	}
	if (i < eng->stats.sprites_count)
		return (1);
	return (0);
}

int 		util_create_animated_sprite(t_engine *eng, char *str, t_sprite *res)
{
	int i;
	int srfc_count;
	char *name;

	i = 0;
	srfc_count = 0;
	/* Подсчет количества фреймов */
	while (i != eng->stats.sprites_count)
	{
		name = util_add_png_num_to_name(str, srfc_count + 1);
		while (i < eng->stats.sprites_count)
		{
			if (!ft_strcmp(name, eng->sprites_buffer[i]->filename))
			{
				srfc_count++;
				free(name);
				i = 0;
				break;
			}
			i++;
		}
	}
	if (srfc_count)
		free(name);
	if (srfc_count)
	{
		res->frames_num = srfc_count;
		res->frames_delay = DEFAULT_SPRITE_DELAY;
		res->a_state = ANIMATE;
		res->surface = (SDL_Surface **) ft_memalloc(sizeof(SDL_Surface *)
													* srfc_count);
		srfc_count = 0;
		while (srfc_count < res->frames_num)
		{
			name = util_add_png_num_to_name(str, srfc_count + 1);
			i = 0;
			while (i < eng->stats.sprites_count)
			{
				if (!ft_strcmp(name, eng->sprites_buffer[i]->filename))
				{
					res->surface[srfc_count] =
							util_transform_texture_to_sprite(
									&eng->sprites_buffer[i]->texture);
					srfc_count++;
					free(name);
					break;
				}
				i++;
			}
		}
		return (1);
	}
	return (0);
}

void		util_create_sprite(t_engine *eng, t_sprite *sprite, char **str)
{
	int 	srfc_count;
	char 	*name;

	util_parsing_error_count_handler("sprite", str, 4);
	util_int10_data_filler(&sprite->id, str[1]);
	util_int10_data_filler(&sprite->frames_num, str[2]);
	util_int10_data_filler(&sprite->frames_delay, str[3]);
	sprite->surface = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *)
												  * sprite->frames_num);
	sprite->a_state = STATIC;
	if (sprite->frames_num > 1)
	{
		sprite->a_state = ANIMATE;
		srfc_count = 1;
		while (srfc_count <= sprite->frames_num)
		{
			name = ft_strcpy(ft_strnew(ft_strlen(str[4]) + 2), str[4]);
			name = ft_strcat(ft_strcat(name, "_"), ft_itoa(srfc_count));
			util_find_sprite_by_name(&sprite->surface[srfc_count], eng, name);
			free(name);
			srfc_count++;
		}
	}
	else
	{
		sprite->a_state = STATIC;
		util_find_sprite_by_name(sprite->surface, eng, str[4]);
	}
	eng->stats.skins_count++;
}
