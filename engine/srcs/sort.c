/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:06:03 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/11 15:09:04 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	sprite_int_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sprite_double_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sprite_comb_sort(t_sector *sect)
{
	int		gap;
	int		j;
	int		i;
	t_bool	swapped;

	gap = sect->sprobjects_count;
	swapped = false;
	while (gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swapped = false;
		i = 0;
		while (i < sect->sprobjects_count - gap)
		{
			j = i + gap;
			if(sect->dist[i] < sect->dist[j])
			{
				sprite_double_swap((sect->dist + i), (sect->dist + j));
				sprite_int_swap((sect->order + i), (sect->order + j));
				swapped = true;
			}
			i++;
		}
	}
}