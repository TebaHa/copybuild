/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 21:48:37 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/26 20:32:11 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#define STB_IMAGE_IMPLEMENTATION
# include "../../lib/stblib/stb_image.h"

t_image			load_textures(const char *fname)
{
	t_image	image;

	image_load(&image, fname);
	return (image);
}

void		image_load(t_image *img, const char *fname)
{
	if ((img->data = stbi_load(fname, &img->width, &img->height, &img->channels, 0)) != NULL)
	{
		img->size = img->height * img->width * img->channels;
		img->allocation_ = STB_ALLOCATED;
	}
}

void		image_create(t_image *img, int width, int height, int channels)
{
	size_t size;

	size = width * height * channels;
	img->data = ft_memalloc(size);
	if (img->data)
	{
		img->width = width;
		img->height = height;
		img->size = size;
		img->channels = channels;
		img->allocation_ = SELF_ALLOCATED;
	}
}

void		image_free(t_image *img)
{
	if (img->allocation_ != NO_ALLOCATION && img->data != NULL)
	{
		if (img->allocation_ != STB_ALLOCATED)
			stbi_image_free(img->data);
		else
			free(img->data);
	}
	ft_bzero((void *)img, sizeof(t_image));
}
