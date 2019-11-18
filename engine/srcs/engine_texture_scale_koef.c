/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_texture_scale_koef.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:58:51 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/18 18:56:48 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

float	count_line_length(t_line_2d line)
{
	float	tmp;
	float	dist;

	tmp = pow((line.b.x - line.a.x), 2)
	+ pow((line.b.y - line.a.y), 2);
	if (tmp <= 0.1)
		return 0;
	dist = sqrt(tmp);
	return (dist);
}

void	prepare_polygones(t_engine *eng)
{
	int			i;
	int			j;
	float		dist;
	t_sector	*s;

	i = 0;
	while (i < eng->stats.sectors_count)
	{
		j = 0;
		s = &eng->world->sectors_array[i];
		while (j < s->objects_count)
		{
			if (s->objects_array[j].polies_array[0].texture != NULL)
			{
				if (s->objects_array[j].polies_array[0].texture_spread == 1 ||
				s->objects_array[j].polies_array[0].texture_spread == 0)
				{
					s->objects_array[j].polies_array[0].tex_scale_koef
					= s->objects_array[j].polies_array[0].texture->height;
				}
				else
				{
					s->objects_array[j].polies_array[0].tex_scale_koef
					= s->objects_array[j].polies_array[0].texture->height
					* s->objects_array[j].polies_array[0].texture_spread;
				}
			}
			else
			{
				if (s->objects_array[j].ceil_wall_spread == 0)
					s->objects_array[j].polies_array[0].tex_scale_koef =
					64;
			}
			j++;
		}
		i++;
	}
}
