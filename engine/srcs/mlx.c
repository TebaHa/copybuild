/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:16:33 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/06 21:00:11 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		init_image(void *mlx, t_image *img, int width, int height)
{
	img->width = width;
	img->height = height;
	img->ptr_img = mlx_new_image(mlx, width, height);
	img->ptr_data = mlx_get_data_addr(img->ptr_img, &img->bpp,
									&img->size_line, &img->endian);
}

void		init_window(t_mxl_win *window)
{
	window->width = WIDTH;
	window->height = HEIGHT;
	window->ptr_mlx	= mlx_init();
	window->ptr_window = mlx_new_window(window->ptr_mlx,
										window->width, window->height, "fps");
}
