/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 23:22:17 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/16 18:08:03 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	init_sectors(t_engine *eng)
{
	t_sector	*sect;
	int			i;

	i = 0;
	while (i < eng->world->sectors_count)
	{
		sect = &eng->world->sectors_array[i];
		sect->opening.id = i;
		sect->opening.renderable = true;
//		sect->color.red = 1;
//		sect->color.green = 0.5;
//		sect->color.blue = 0.5;
		i++;
	}
}
