/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_door_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:53:42 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/12 23:25:37 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			engine_run_doors(t_engine *eng, t_door_task **stack)
{
	int	i;

	i = 0;
	while (i < MAX_DOORS)
	{
		if (stack[i])
		{
			if (execute_door(stack[i],
			&eng->world->sectors_array[stack[i]->id]))
				engine_flush_doorqueue((stack + i));
		}
		i++;
	}
}

int				close_door(t_door_task *door, t_sector *sect)
{
	sect->ceil -= door->delta;
	sect->floor += door->delta;
	if (abs(sect->ceil - sect->floor) <= 50)
	{
		door->closed = true;
		return (1);
	}
	return (0);
}

int				open_door(t_door_task *door, t_sector *sect)
{
	sect->ceil += door->delta;
	sect->floor -= door->delta;
	if ((sect->ceil - sect->floor) >= door->range)
	{
		door->closed = false;
		return (1);
	}
	return (0);
}

int				execute_door(t_door_task *door, t_sector *sect)
{
	int	res;

	if (door->closed == false)
		res = close_door(door, sect);
	else
		res = open_door(door, sect);
	return (res);
}

void			engine_push_doorqueue(t_door_task **stack,
				t_door_task *item)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
		i++;
	while ((i + 1) < MAX_DOORS && i >= 0)
	{
		stack[i + 1] = stack[i];
		i--;
	}
	stack[0] = item;
}

void			engine_flush_doorqueue(t_door_task **stack)
{
	*stack = NULL;
}
