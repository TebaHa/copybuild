/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:12:54 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 18:36:26 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_push_renderstack(t_item *renderqueue, t_item item)
{
	int	i;

	i = 0;
	while (renderqueue[i].sectorno >= 0)
		i++;
	while ((i + 1) < MAXSECTORS && i >= 0)
	{
		renderqueue[i + 1] = renderqueue[i];
		i--;
	}
	renderqueue[0] = item;
}

t_item		engine_pop_renderstack(t_item *renderqueue)
{
	t_item	res;
	int		i;

	i = 0;
	res = renderqueue[0];
	while ((i + 1) < MAXSECTORS && renderqueue[i].sectorno >= 0)
	{
		renderqueue[i] = renderqueue[i + 1];
		i++;
	}
	return (res);
}

void		engine_clear_renderstack(t_item *renderqueue)
{
	int	i;

	i = 0;
	while (i < MAXSECTORS)
	{
		renderqueue[i].sectorno = -1;
		i++;
	}
}
