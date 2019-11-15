/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_transprt_stack.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:50:21 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/15 17:45:10 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			engine_push_tsrenderstack(t_trns_item *renderqueue,
				t_trns_item item)
{
	int	i;

	i = 0;
	while (renderqueue[i].status != 0)
		i++;
	while ((i + 1) < 128 && i >= 0)
	{
		renderqueue[i + 1] = renderqueue[i];
		i--;
	}
	renderqueue[0] = item;
	renderqueue[0].status = 1;
}

void			engine_clear_tsrenderstack(t_trns_item *renderqueue)
{
	int	i;

	i = 0;
	while (i < 128)
	{
		renderqueue[i++].status = 0;
		renderqueue[i++].sprite_renderstack = NULL;
	}
}

t_trns_item		engine_pop_tsrenderstack(t_trns_item *renderqueue)
{
	t_trns_item	node;
	int			i;

	node = renderqueue[0];
	i = 0;
	while ((i + 1) < 128 && renderqueue[i].status != 0)
	{
		renderqueue[i] = renderqueue[i + 1];
		i++;
	}
	return (node);
}
