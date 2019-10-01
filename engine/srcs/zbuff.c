/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zbuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:28:28 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/01 20:56:24 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		zbuff_zeroed(int *zbuff)
{
	int		x;
	int		y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			zbuff[y * WIDTH + x] = INT32_MIN;
			y++;
		}
		x++;
	}
}