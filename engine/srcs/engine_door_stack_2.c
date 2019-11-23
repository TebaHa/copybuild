/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_door_stack_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:01:36 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 16:41:57 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int		close_door(t_door_task *door, t_sector *sect)
{
	sect->ceil -= door->delta;
	sect->floor += door->delta;
	sect->opening.inuse = true;
	if (abs(sect->ceil - sect->floor) <= 50)
	{
		door->renderable = false;
		sect->opening.inuse = false;
		door->closed = true;
		return (1);
	}
	return (0);
}

int		open_door(t_door_task *door, t_sector *sect)
{
	sect->ceil += door->delta;
	sect->floor -= door->delta;
	door->renderable = true;
	sect->opening.inuse = true;
	if ((sect->ceil - sect->floor) >= door->range)
	{
		sect->opening.inuse = false;
		door->closed = false;
		return (1);
	}
	return (0);
}
