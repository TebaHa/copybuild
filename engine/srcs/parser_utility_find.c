/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utility_find.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:56:36 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/14 11:56:19 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		util_find_texture_by_name(t_image **dst, t_engine *eng,
			char *name)
{
	int		i;
	int		find;
	char	*name_png;

	i = 0;
	find = 0;
	name_png = ft_strnew(ft_strlen(name) + ft_strlen(".png"));
	name_png = ft_strcat(ft_strcpy(name_png, name), ".png");
	while (i < eng->stats.textures_count)
	{
		if (!ft_strcmp(name_png, eng->texture_buffer[i]->filename))
		{
			*dst = &eng->texture_buffer[i]->texture;
			find = 1;
		}
		i++;
	}
	if (i >= eng->stats.textures_count && !find)
		util_parsing_error_no_texture(dst, eng, name);
	free(name_png);
}

void		util_find_sprite_by_name(SDL_Surface *dst, t_engine *eng,
			char *name)
{
	int		i;
	int		find;
	char	*name_png;

	/* Не реализовано несколько спрайтов на одно событие */
	i = 0;
	find = 0;
	if (!name)
	{
		/* Обработка ситуации, когда нет текстуры */
		dst = NULL;
		return ;
	}
	name_png = ft_strnew(ft_strlen(name) + ft_strlen(".png"));
	name_png = ft_strcat(ft_strcpy(name_png, name), ".png");
	while (i < eng->stats.sprites_count)
	{
		if (!ft_strcmp(name_png, eng->sprites_buffer[i]->filename))
		{

			dst = util_transform_texture_to_sprite(&eng->sprites_buffer[i]->texture);
			find = 1;
		}
		i++;
	}
	if (i >= eng->stats.textures_count && !find)
		util_parsing_error_no_sprite(dst, eng, name);
	free(name_png);
}
