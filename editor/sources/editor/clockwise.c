/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clockwise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:02:54 by djast             #+#    #+#             */
/*   Updated: 2019/11/24 17:17:30 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		is_clockwise(t_walls *walls)
{
	int result;

	result = (walls->neighbour_x1 - walls->x1) * (walls->y2 - walls->y1) -
			(walls->neighbour_y1 - walls->y1) * (walls->x2 - walls->x1);
	if (result < 0)
		return (1);
	return (0);
}
