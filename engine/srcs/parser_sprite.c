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

void		util_create_sprite(t_engine *eng, t_sprite *sprite, char **str)
{
	int		srfc_count;

	util_parsing_error_count_handler("sprite", str, 4);
	sprite->id = util_int10_data_filler(str[1], 0, 0xFFFF);
	sprite->frames_num = util_int10_data_filler(str[2], 0, 0xFFFF);
	sprite->frames_delay = util_int10_data_filler(str[3], 0, 0xFFFF);
	sprite->surface = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *)
		* sprite->frames_num);
	sprite->a_state = STATIC;
	if (sprite->frames_num > 1)
	{
		sprite->a_state = ANIMATE;
		srfc_count = 1;
		while (srfc_count <= sprite->frames_num)
		{
			util_create_sprite_with_num(eng, sprite, str, srfc_count);
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

void		util_create_sprite_with_num(t_engine *eng, t_sprite *sprite,
			char **str, int srfc_count)
{
	char	*name;

	name = ft_strcpy(ft_strnew(ft_strlen(str[4]) + 2), str[4]);
	name = ft_strcat(ft_strcat(name, "_"), ft_itoa(srfc_count));
	util_find_sprite_by_name(&sprite->surface[srfc_count], eng, name);
	free(name);
}

t_sprite	*util_create_sprite_by_name(t_engine *eng, char *str)
{
	t_sprite *res;

	res = (t_sprite *)ft_memalloc(sizeof(t_sprite));
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

void		util_find_sprite_by_name(SDL_Surface **dst, t_engine *eng,
			char *name)
{
	int		i;
	char	*name_png;

	i = 0;
	if (!name)
	{
		*dst = NULL;
		return ;
	}
	name_png = util_add_png_to_name(name);
	while (i < eng->stats.sprites_count)
	{
		if (!ft_strcmp(name_png, eng->sprites_buffer[i]->filename))
		{
			*dst = util_transform_texture_to_sprite(
					&eng->sprites_buffer[i]->texture);
			break ;
		}
		i++;
	}
	free(name_png);
	if (i == eng->stats.sprites_count)
		util_parsing_error_no_sprite(dst, eng, name);
	else
		eng->stats.cycle_detector = 0;
}
