/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:06:03 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/04 14:22:56 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	sprite_info_swap(t_spr_info *a, t_spr_info *b)
{
	t_spr_info	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	comb_sort(t_spr_info *info_array, int amount)
{
	int		gap;
	int		j;
	t_bool	swapped;

	gap = amount;
	swapped = false;
	while(gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		if(gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swapped = false;
		for(int i = 0; i < amount - gap; i++)
		{
			j = i + gap;
			if(info_array[i].sprite_dist < info_array[j].sprite_dist)
			{
				sprite_info_swap((info_array + i), (info_array + j));
				swapped = true;
			}
		}
	}
}