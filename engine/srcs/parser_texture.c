/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:56:36 by fsmith            #+#    #+#             */
/*   Updated: 2019/11/02 02:56:49 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		util_find_texture_by_name(t_image **dst, t_engine *eng,
			char **name, int *spread)
{
	int		i;
	int		find;
	char	*name_png;

	util_find_texture_spread(spread, name);
	i = 0;
	find = 0;
	name_png = ft_strnew(ft_strlen(*name) + ft_strlen(".png"));
	name_png = ft_strcat(ft_strcpy(name_png, *name), ".png");
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
		util_parsing_error_no_texture(dst, eng, *name);
	else
		eng->stats.cycle_detector = 0;
	free(name_png);
}

void		util_find_texture_spread(int *spread, char **str)
{
	char	*spreading;

	if ((spreading = ft_strcut(str, ',')))
	{
		*spread = util_int10_data_filler(spreading, 0, 0xFFFF);
		free(spreading);
	}
	else
		*spread = 0;
}

char		*ft_strcut(char **s, char c)
{
	char	*output;
	char	*str;
	size_t	c_pos;
	size_t	len;

	if (!ft_strchr(*s, c))
		return (NULL);
	c_pos = ft_strchr(*s, c) - *s;
	len = ft_strlen(*s) - c_pos;
	if (!(str = ft_strsub(*s, 0, c_pos)))
		return (NULL);
	if (len > 0)
		output = ft_strsub(*s, (unsigned int)c_pos + 1, len);
	else
		output = (ft_strnew(0));
	free(*s);
	*s = str;
	return (output);
}

SDL_Surface	*util_transform_texture_to_sprite(t_image *texture)
{
	SDL_Surface	*sprite;
	t_int_4		p;

	if (texture == NULL)
		return (NULL);
	sprite = util_create_rgb_surface(0, texture->width, texture->height, 32);
	p.pix = sprite->pixels;
	p.x = 0;
	while (p.x < sprite->w)
	{
		p.y = 0;
		while (p.y < sprite->h)
		{
			p.offsets = p.y * sprite->w + p.x;
			p.offseti = p.y * texture->width + p.x;
			p.pix[p.offsets] = ((unsigned *)texture->data)[p.offseti];
			p.y++;
		}
		p.x++;
	}
	return (sprite);
}

SDL_Surface	*util_create_rgb_surface(Uint32 flags, int width, int height,
			int depth)
{
	return (SDL_CreateRGBSurface(flags, width, height, depth,
		(Uint32)0xff000000, (Uint32)0x00ff0000,
		(Uint32)0x0000ff00, (Uint32)0x000000ff));
}
