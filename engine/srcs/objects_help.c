/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:16:46 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/01 08:14:32 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int		intersect_sect(t_point_2d a, t_point_2d b, t_point_2d pos)
{
	if (((a.y > pos.y) != (b.y > pos.y)) &&
	(pos.x < (a.x + (b.x - a.x)
	* (pos.y - a.y) / (b.y - a.y))))
		return (1);
	else
		return (0);
}
