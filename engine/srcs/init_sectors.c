/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 23:22:17 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 17:31:02 by zytrams          ###   ########.fr       */
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
		sect->opening.inuse = false;
		sect->opening.real_ceil = sect->ceil;
		sect->opening.real_floor = sect->floor;
		i++;
	}
}
