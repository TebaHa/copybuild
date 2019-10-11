/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_stack.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:12:17 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/11 15:16:49 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

void			engine_push_spriterenderstack(t_item_sprts **renderqueue, t_item_sprts *item)
{
	int	i;

	i = 0;
	while (renderqueue[i] != NULL)
		i++;
	while ((i + 1) < MAXSECTORS && i >= 0)
	{
		renderqueue[i + 1] = renderqueue[i];
		i--;
	}
	renderqueue[0] = item;
}

void			engine_clear_spriterenderstack(t_item_sprts **renderqueue)
{
	int	i;

	i = 0;
	while (i < MAXSECTORS)
		renderqueue[i++] = NULL;
}

t_item_sprts	*engine_pop_spriterenderstack(t_item_sprts **renderqueue)
{
	t_item_sprts	*node;
	int				i;

	node = renderqueue[0];
	i = 0;
	while ((i + 1) < MAXSECTORS && renderqueue[i] != NULL)
	{
		renderqueue[i] = renderqueue[i + 1];
		i++;
	}
	return (node);
}