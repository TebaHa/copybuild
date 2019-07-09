/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:17:20 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/09 20:28:34 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_create_test_world(t_world **world)
{
	*world = (t_world *)ft_memalloc(sizeof(t_world));
	(*world)->sectors_array = (t_sector *)ft_memalloc(sizeof(t_sector) * 2);
	(*world)->sectors_array[0].objects_array = (t_object *)ft_memalloc(sizeof(t_object) * 4);
	(*world)->sectors_array[0].objects_array[0] = engine_create_obj_wall(-1, (t_point_3d){-100, -100, 75}, (t_point_3d){-100, -100, 25},
	(t_point_3d){100, -100, 25}, (t_point_3d){100, -100, 75});
	(*world)->sectors_array[0].objects_array[1] = engine_create_obj_wall(-1, (t_point_3d){100, -100, 75}, (t_point_3d){100, -100, 25},
	(t_point_3d){100, 100, 25}, (t_point_3d){100, 100, 75});
	(*world)->sectors_array[0].objects_array[2] = engine_create_obj_wall(1, (t_point_3d){100, 100, 75}, (t_point_3d){100, 100, 25},
	(t_point_3d){-100, 100, 25}, (t_point_3d){-100, 100, 75});
	(*world)->sectors_array[0].objects_array[3] = engine_create_obj_wall(-1, (t_point_3d){-100, 100, 75}, (t_point_3d){-100, 100, 25},
	(t_point_3d){-100, -100, 25}, (t_point_3d){-100, -100, 75});
	(*world)->sectors_array[1].objects_array = (t_object *)ft_memalloc(sizeof(t_object) * 4);
	(*world)->sectors_array[1].objects_array[0] = engine_create_obj_wall(0, (t_point_3d){100, 100, 75}, (t_point_3d){100, 100, 25},
	(t_point_3d){-100, 100, 25}, (t_point_3d){-100, 100, 75});
	(*world)->sectors_array[1].objects_array[1] = engine_create_obj_wall(-1, (t_point_3d){-100, 100, 25}, (t_point_3d){-100, 100, 75},
	(t_point_3d){-200, 200, 25}, (t_point_3d){-200, 200, 75});
	(*world)->sectors_array[1].objects_array[2] = engine_create_obj_wall(-1, (t_point_3d){-200, 200, 25}, (t_point_3d){-200, 200, 75},
	(t_point_3d){-100, 200, 25}, (t_point_3d){-100, 200, 75});
	(*world)->sectors_array[1].objects_array[3] = engine_create_obj_wall(-1, (t_point_3d){-100, 200, 25}, (t_point_3d){-100, 200, 75},
	(t_point_3d){100, 100, 25}, (t_point_3d){100, 100, 75});
}

t_object	engine_create_obj_wall(int portal, t_point_3d a, t_point_3d b, t_point_3d c, t_point_3d d)
{
	t_object	wall;

	wall.sector = portal;
	wall.polies_array = (t_polygone *)ft_memalloc(sizeof(t_polygone));
	wall.polies_array->vertices_size = 4;
	wall.polies_array->vertices = (t_point_3d *)ft_memalloc(sizeof(t_point_3d) * 4);
	wall.polies_array->vertices[0] = a;
	wall.polies_array->vertices[1] = b;
	wall.polies_array->vertices[2] = c;
	wall.polies_array->vertices[3] = d;
	return (wall);
}
