/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_point_3d	*engine_read_vertexes_from_file(t_engine *eng, char **json_splited)
{
	t_point_3d	*v_arr_buffer;
	char		**splitted_line;
	int			i;

	v_arr_buffer = (t_point_3d *)ft_memalloc(sizeof(t_point_3d) *
		eng->stats.vertexes_count);
	i = 0;
	eng->stats.vertexes_count = 0;
	while (json_splited[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splitted_line[0], "vertex:") == 0)
			util_create_point_3d(eng, &v_arr_buffer[eng->stats.vertexes_count],
				splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (v_arr_buffer);
}

void		util_create_point_3d(t_engine *eng, t_point_3d *point, char **str)
{
	util_parsing_error_count_handler("vertex", str, 4);
	util_int10_data_filler(&point->id, str[1]);
	util_float10_data_filler(&point->x, str[2]);
	util_float10_data_filler(&point->y, str[3]);
	util_float10_data_filler(&point->z, str[4]);
	eng->stats.vertexes_count++;
}

t_point_3d	util_get_vertex_from_buff_by_id(int id, int size,
			t_point_3d *vertexes, int polygone_id)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (vertexes[i].id == id)
			break ;
		i++;
	}
	if (i == size)
		util_parsing_error_lost_handler("vertex", id, "polygone", polygone_id);
	return (vertexes[i]);
}

void		util_release_vertex_buffer(t_point_3d *vertex_buff)
{
	free(vertex_buff);
}
