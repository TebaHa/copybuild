/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:25:21 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 15:25:35 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_clear_surface(SDL_Surface *surf)
{
	SDL_memset(surf->pixels, 0, surf->h * surf->pitch);
}

void		one_dim_zbuffers_copy(t_item_sprts *sprt, int *ytop, int *ybottom)
{
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		sprt->ytop[i] = ytop[i];
		sprt->ybottom[i] = ybottom[i];
		i++;
	}
}
