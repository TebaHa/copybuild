/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:09:11 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/22 22:12:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	get_relative_xy(t_engine *eng, t_fix_point_2d *p)
{
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	*p = (t_fix_point_2d){x - eng->x, eng->y - y};
	eng->x = x;
	eng->y = y;
}
