/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:59:50 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/12 21:35:05 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

/*
int		intersect3D_SegmentPlane( Segment S, Plane Pn, t_point_3d *res)
{
	t_point_3d	u;
	t_point_3d	w;

	u = S.P1 - S.P0;
	w = S.P0 - Pn.V0;
	float     D = dot(Pn.n, u);
	float     N = -dot(Pn.n, w);

	if (fabs(D) < SMALL_NUM) {           // segment is parallel to plane
		if (N == 0)                      // segment lies in plane
			return 2;
		else
			return 0;                    // no intersection
	}
	// they are not parallel
	// compute intersect param
	float sI = N / D;
	if (sI < 0 || sI > 1)
		return 0;                        // no intersection

	*I = S.P0 + sI * u;                  // compute segment intersect point
	return 1;
}

void	engine_push_particlestack(t_point_3d *particlestack, int *status, t_point_3d point)
{
	particlestack[*status] = point;
	if ((*status) >= MAXSHOOTHOLES - 1)
		*status = 0;
	else
		*status = *status + 1;
}
*/