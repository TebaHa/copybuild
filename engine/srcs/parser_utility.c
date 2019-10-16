/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:12:50 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 19:07:36 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

SDL_Surface	*util_CreateRGBSurface(Uint32 flags, int width, int height,
		int depth)
{
	return (SDL_CreateRGBSurface(flags, width, height, depth,
		(Uint32)0xff000000, (Uint32)0x00ff0000, (Uint32)0x0000ff00, (Uint32)0x000000ff));
}

SDL_Surface	*util_transform_texture_to_sprite(t_image *texture)
{
	SDL_Surface	*sprite;
	int 		x;
	int 		y;
	int 		offsets;
	int 		offseti;
	unsigned	*pix;

	if (texture == NULL)
		return (NULL);
	sprite = util_CreateRGBSurface(0, texture->width, texture->height, 32);
	pix = sprite->pixels;
	x = 0;
	while (x < sprite->w)
	{
		y = 0;
		while (y < sprite->h)
		{
			offsets = y * sprite->w + x;
			offseti = y * texture->width + x;
			pix[offsets] = ((unsigned *)texture->data)[offseti];
			y++;
		}
		x++;
	}
	//image_free(texture);
	return (sprite);
}

void		util_release_read_buffers(t_buff *buff)
{
	free(buff->vertexes);
	free(buff->polies);
	free(buff->objects);
	free(buff->sprobjects);
	free(buff->sprites);
	util_release_char_matrix(buff->str);
}

void		infinite_loop(void)
{
	while (1)
		;
}

char		*util_add_png_to_name(char *old_name)
{
	char	*new_name;

	new_name = ft_strjoin(old_name, ".png");
	return (new_name);
}

char		*util_add_png_num_to_name(char *old_name, int num)
{
	char	*new_name;
	char 	*new_num;

	new_num = ft_itoa(num);
	new_name = ft_strnew(ft_strlen(old_name) + ft_strlen("_.png")
						 + ft_strlen(new_num));
	new_name = ft_strcpy(new_name, old_name);
	new_name = ft_strcat(new_name, "_");
	new_name = ft_strcat(new_name, new_num);
	new_name = ft_strcat(new_name, ".png");
	free(new_num);
	return (new_name);
}
