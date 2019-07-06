/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:37:45 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/06 22:07:43 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_engine		*init_engine(void)
{
	t_engine	*eng;

	eng = (t_engine *)ft_memalloc(sizeof(t_engine));
	init_window(&eng->window);
	init_image(eng->window.ptr_mlx, &eng->img, eng->window.width, eng->window.height);
	create_portal_map(&eng->portals);
	return		(eng);
}
