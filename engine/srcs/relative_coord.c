/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:09:11 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 20:17:59 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	get_relative_xy(t_engine *eng, t_fix_point_2d *p)
{
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	*p = (t_fix_point_2d){x - eng->x, y - eng->y};
	eng->x = x;
	eng->y = y;
}
