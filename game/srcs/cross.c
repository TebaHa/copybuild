/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:58:58 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/07 21:01:50 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

t_point		intersect(t_point a, t_point b, t_point c, t_point d)
{
	t_point res;
	long	det;

	res.x = dot_cross(a, b);
	res.y = dot_cross(c, d);
	det = dot_cross((t_point){a.x - b.x, a.y - b.y, 0}, (t_point){c.x - d.x, c.y - d.y, 0});
	res.x =	dot_cross((t_point){res.x, a.x - b.x, 0}, (t_point){res.y, c.x - d.x, 0}) / det;
	res.y =	dot_cross((t_point){res.x, a.y - b.y, 0}, (t_point){res.y, c.y - d.y, 0}) / det;
	return (res);
}

long	dot_cross(t_point a, t_point b)
{
	long res;

	res = a.x * b.y - a.y * b.x;
	return (res);
}
