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

	if ((v_arr_buffer = (t_point_3d *)ft_memalloc(sizeof(t_point_3d) *
	eng->stats.vertexes_count)) == NULL)
		util_malloc_error("vert_buffer");
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
	util_find_repeats_in_vertexes(v_arr_buffer, eng->stats.vertexes_count);
	return (v_arr_buffer);
}

void		util_create_point_3d(t_engine *eng, t_point_3d *point, char **str)
{
	util_parsing_error_little_data_check("sector", str, 4);
	util_parsing_error_count_handler("vertex", str, 4);
	point->id = util_int10_data_filler(str[1], 0, 0xFFFF);
	point->x = util_float10_data_filler(str[2], -8000, 8000);
	point->y = util_float10_data_filler(str[3], -8000, 8000);
	point->z = util_float10_data_filler(str[4], -5000, 5000);
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

void		util_find_repeats_in_vertexes(t_point_3d *vertex,
			int vertexes_count)
{
	int		j;
	int		i;

	i = 0;
	while (i < vertexes_count)
	{
		j = 0;
		while (j < vertexes_count)
		{
			if (vertex[i].id == vertex[j].id && i != j)
				util_parsing_error_repeats("vertexes", "null", vertex[i].id);
			j++;
		}
		i++;
	}
}

void		util_release_vertex_buffer(t_point_3d *vertex_buff)
{
	free(vertex_buff);
}
