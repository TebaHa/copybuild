/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:06:03 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 19:54:01 by zytrams          ###   ########.fr       */
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

void	sprite_float_swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sprite_comb_sort(t_sector *sect)
{
	t_sorter	data;

	data.gap = sect->sprobjects_count;
	data.swapped = false;
	while (data.gap > 1 || data.swapped)
	{
		sprite_comb_sort_help(&data);
		while (data.i < sect->sprobjects_count - data.gap)
		{
			data.j = data.i + data.gap;
			if (sect->dist[data.i] < sect->dist[data.j])
			{
				sprite_float_swap((sect->dist + data.i),
				(sect->dist + data.j));
				sprite_int_swap((sect->order + data.i),
				(sect->order + data.j));
				data.swapped = true;
			}
			data.i++;
		}
	}
}

void	sprite_comb_sort_help(t_sorter *data)
{
	data->gap = (data->gap * 10) / 13;
	if (data->gap == 9 || data->gap == 10)
		data->gap = 11;
	if (data->gap < 1)
		data->gap = 1;
	data->swapped = false;
	data->i = 0;
}
