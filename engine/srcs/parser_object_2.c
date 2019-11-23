/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_object_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			util_find_repeats_in_objects(t_object *object,
				int objects_count)
{
	int			j;
	int			i;

	i = 0;
	while (i < objects_count)
	{
		j = 0;
		while (j < objects_count)
		{
			if (object[i].id == object[j].id && i != j)
				util_parsing_error_repeats("objects", "null", object[i].id);
			j++;
		}
		i++;
	}
}

void			util_release_objects_buffer(t_object *object_buff, int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		util_release_vertex_buffer(object_buff[i].polies_array->vertices_array);
		i++;
	}
	free(object_buff);
}

void			util_parsing_objects_portal(t_engine *eng, t_buff buff)
{
	int			sect_count;
	int			obj_count;
	int			find;

	obj_count = 0;
	while (obj_count < eng->stats.objects_count)
	{
		find = 0;
		sect_count = 0;
		while (sect_count < eng->stats.sectors_count)
		{
			if (buff.objects[obj_count].portal == buff.sectors[sect_count].id
				|| buff.objects[obj_count].portal == -1)
				find = 1;
			sect_count++;
		}
		if (find != 1)
		{
			ft_putendl("Parsing error:");
			ft_putstr("Portal error!\n");
			close_game(PARSING_ERROR);
		}
		obj_count++;
	}
}
