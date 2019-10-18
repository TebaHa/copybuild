/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:56:36 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/28 12:35:34 by fsmith           ###   ########.fr       */
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
	else
		eng->stats.cycle_detector = 0;
	free(name_png);
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
