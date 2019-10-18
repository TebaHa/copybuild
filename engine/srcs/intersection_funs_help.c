/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_funs_help.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:56:03 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 17:40:15 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

float		min(float a, float b)
{
	return ((a < b) ? a : b);
}

float		max(float a, float b)
{
	return ((a > b) ? a : b);
}

float		clamp(float a, float mi, float ma)
{
	return (min(max(a, mi), ma));
}

float		vxs(float x0, float y0, float x1, float y1)
{
	return (x0 * y1 - x1 * y0);
}

/*
** Overlap:  Determine whether the two number ranges overlap.
*/
short		overlap(float a0, float a1, float b0, float b1)
{
	return (min(a0, a1) <= max(b0, b1)
	&& min(b0, b1) <= max(a0, a1));
}
