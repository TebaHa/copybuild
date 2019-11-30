/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:50:53 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/30 18:19:11 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	point_swapper_shoot(float *t0, float *t1, float a, float b)
{
	if (a > b)
	{
		*t0 = a;
		*t1 = b;
	}
	else
	{
		*t1 = a;
		*t0 = b;
	}
}

void	kill(t_sprobject *sobj)
{
	int	i;

	i = 0;
	if (sobj->enum_type == IMP ||
	sobj->enum_type == AFRIT ||
	sobj->enum_type == CACODEMON)
	{
		sobj->state = E_DEAD;
		sobj->type->anmtn[E_DEAD]->a_state = ANIMATE;
		while (i < 8)
		{
			sobj->type->anmtn_360[E_DEAD][i]->a_state = ANIMATE;
			i++;
		}
		sobj->frame_num = 0;
	}
}
