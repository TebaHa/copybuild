/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_polygone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

//t_polygone		*engine_read_polygones_from_file(t_engine *eng, t_buff buff)
//{
//	t_polygone	*p_array_buffer;
//	char		**splitted_line;
//	int			i;
//
//	p_array_buffer = (t_polygone *)ft_memalloc(sizeof(t_polygone)
//		* eng->stats.polies_count);
//	i = 0;
//	eng->stats.polies_count = 0;
//	while (buff.str[i] != NULL)
//	{
//		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
//		if (ft_strcmp(splitted_line[0], "polygone:") == 0)
//			util_create_polygone(eng, &p_array_buffer[eng->stats.polies_count],
//				buff.vertexes, splitted_line);
//		util_release_char_matrix(splitted_line);
//		i++;
//	}
//	return (p_array_buffer);
//}

//void			util_create_polygone(t_engine *eng, t_polygone *polygone,
//				t_point_3d *vertex_array, char **str)
//{
//	int			vert_count;
//	int			str_count;
//
//	util_parsing_error_little_data_check("polygone", str, 6);
//	polygone->id = util_int10_data_filler(str[1], 0, 0xFFFF);
//	polygone->type = util_int10_data_filler(str[2], 1, 1);
//	util_find_texture_by_name(&polygone->texture, eng, str[3]);
//	polygone->vertices_count = util_int10_data_filler(str[4], 0, 0xFFFF);
//	if (!polygone->vertices_count)
//		util_parsing_error_little_data("vertices", "polygone", str);
//	util_parsing_error_count_handler("polygone", str,
//		4 + polygone->vertices_count);
//	polygone->vertices_array = (t_point_3d *)ft_memalloc(sizeof(t_point_3d)
//		* polygone->vertices_count);
//	str_count = 5;
//	vert_count = 0;
//	while (str_count < 5 + polygone->vertices_count)
//		polygone->vertices_array[vert_count++] =
//			util_get_vertex_from_buff_by_id(ft_atoi(str[str_count++]),
//			eng->stats.vertexes_count, vertex_array, polygone->id);
//	if (polygone->vertices_array[0].id == polygone->vertices_array[1].id)
//		util_parsing_error_repeats("vertexes", "polygone", polygone->id);
//	eng->stats.polies_count++;
//}

//t_polygone		util_get_polygone_from_buff_by_id(int id, int size,
//				t_polygone *polies, int object_id)
//{
//	int			i;
//
//	i = 0;
//	while (i < size)
//	{
//		if (polies[i].id == id)
//			break ;
//		i++;
//	}
//	if (i == size)
//		util_parsing_error_lost_handler("polygone", id, "object", object_id);
//	return (polies[i]);
//}

//void			util_release_polies_buffer(t_polygone *polies_buff, int size)
//{
//	int		i;
//
//	i = 0;
//	while (i < size)
//	{
//		util_release_vertex_buffer(polies_buff[i].vertices_array);
//		i++;
//	}
//	free(polies_buff);
//}
