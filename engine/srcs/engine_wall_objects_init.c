/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_wall_objects_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 09:21:18 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/02 09:29:54 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

/*
void		wall_objects_init(t_object *obj, t_wobj *txtr,
		void *d[2], t_point_3d particle)
{
	t_sh_part	data;
	t_wallobj	*particlestack;
	int			*status;

	particlestack = (t_wallobj *)d[0];
	status = (int *)d[1];
	data.dx1 = obj->polies_array[0].vertices_array[0].x - particle.x;
	data.dy1 = obj->polies_array[0].vertices_array[0].y - particle.y;
	data.dx2 = particle.x - obj->polies_array[0].vertices_array[1].x;
	data.dy2 = particle.y - obj->polies_array[0].vertices_array[1].y;
	data.dist1 = sqrtf(data.dx1 * data.dx1 + data.dy1 * data.dy1);
	data.dist2 = sqrtf(data.dx2 * data.dx2 + data.dy2 * data.dy2);
	data.half_w = txtr-> / 12;
	data.half_w = txtr->bullet_hole.surface[0].w / 12;
	data.w_partcle.texture = wpn->bullet_hole;
	data.w_partcle.a.x = particle.x - ((data.half_w * (particle.x
	- obj->polies_array[0].vertices_array[0].x)) / data.dist1);
	data.w_partcle.a.y = particle.y - ((data.half_w * (particle.y
	- obj->polies_array[0].vertices_array[0].y)) / data.dist1);
	data.w_partcle.b.x = particle.x - ((data.half_w * (particle.x
	- obj->polies_array[0].vertices_array[1].x)) / data.dist2);
	data.w_partcle.b.y = particle.y - ((data.half_w * (particle.y
	- obj->polies_array[0].vertices_array[1].y)) / data.dist2);
	data.w_partcle.id = 1;
	data.w_partcle.z = particle.z;
	data.w_partcle.timer = 0;
	data.w_partcle.frame_num = 0;
	particlestack[*status] = data.w_partcle;
	*status = (*status > 126) ? 0 : *status + 1;
}
*/
