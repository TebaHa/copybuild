/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:14:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/18 18:47:30 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_push_renderstack(int *renderqueue, int sector_id)
{
	int	i;

	i = 0;
	while (renderqueue[i] >= 0)
		i++;
	while ((i + 1) < MAXSECTORS && i >= 0)
	{
		renderqueue[i + 1] = renderqueue[i];
		i--;
	}
	renderqueue[0] = sector_id;
}

int		engine_pop_renderstack(int *renderqueue)
{
	int	res;
	int	i;

	i = 0;
	res = renderqueue[0];
	while ((i + 1) < MAXSECTORS && renderqueue[i] >= 0)
	{
		renderqueue[i] = renderqueue[i + 1];
		i++;
	}
	return (res);
}

void	engine_clear_renderstack(int *renderqueue)
{
	int	i;

	i = 0;
	while (i < MAXSECTORS)
	{
		renderqueue[i] = -1;
		i++;
	}
}
