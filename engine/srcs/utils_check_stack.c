/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:09:33 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/27 20:11:59 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_push_checkstack(int *stack, int sect)
{
	int	i;

	i = 0;
	while (stack[i] >= 0)
		i++;
	while ((i + 1) < MAXSECTORS && i >= 0)
	{
		stack[i + 1] = stack[i];
		i--;
	}
	stack[0] = sect;
}

int		engine_pop_checkstack(int *stack)
{
	int	res;
	int	i;

	i = 0;
	res = stack[0];
	while ((i + 1) < MAXSECTORS && stack[i] >= 0)
	{
		stack[i] = stack[i + 1];
		i++;
	}
	return (res);
}

void	engine_clear_checkstack(int *stack)
{
	int	i;

	i = 0;
	while (i < MAXSECTORS)
	{
		stack[i] = -1;
		i++;
	}
}
