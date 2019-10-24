/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:14:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/24 12:47:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			point_swap_3(t_fix_point_3d *t0, t_fix_point_3d *t1)
{
	t_fix_point_3d		tmp;

	tmp.x = t0->x;
	tmp.y = t0->y;
	tmp.z = t0->z;
	t0->x = t1->x;
	t0->y = t1->y;
	t0->z = t1->z;
	t1->x = tmp.x;
	t1->y = tmp.y;
	t1->z = tmp.z;
}

void			point_swap_2(t_fix_point_2d *t0, t_fix_point_2d *t1)
{
	t_fix_point_2d		tmp;

	tmp.x = t0->x;
	tmp.y = t0->y;
	t0->x = t1->x;
	t0->y = t1->y;
	t1->x = tmp.x;
	t1->y = tmp.y;
}
