/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/08/07 20:44:22 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_world		*engine_read_world_from_file(t_engine *eng, char **json_splited)
{
	t_world	*res_world;
	char	**splited_line;
	int		i;

	i = 0;
	while (json_splited[i])
	{
		if (ft_strwcmp(json_splited[i], "world:") == 0)
		{
			splited_line = ft_strsplitwhitespaces(json_splited[i]);
			util_create_world(&res_world, splited_line);
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	return (res_world);
}

t_point_3d	*engine_read_vertexes_from_file(t_engine *eng, char **json_splited)
{
	t_point_3d	*v_arr_buffer;
	char		**splited_line;
	int			i;

	i = 0;
	eng->stats.vertexes_count = 0;
	while (json_splited[i] != NULL)
		if (ft_strwcmp(json_splited[i++], "vertex:") == 0)
			eng->stats.vertexes_count++;
	v_arr_buffer = (t_point_3d *)ft_memalloc(sizeof(t_point_3d) *
		eng->stats.vertexes_count);
	i = 0;
	eng->stats.vertexes_count = 0;
	while (json_splited[i] != NULL)
	{
		splited_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splited_line[0], "vertex:") == 0)
			util_create_point_3d(eng, &v_arr_buffer[eng->stats.vertexes_count],
			splited_line);
		util_release_char_matrix(splited_line);
		i++;
	}
	return (v_arr_buffer);
}

t_object	*engine_read_objects_from_file(t_engine *eng,
			t_polygone *polies_array, char **json_splited)
{
	t_object	*o_array_buffer;
	char		**splited_line;
	int			i;

	i = 0;
	eng->stats.objects_count = 0;
	while (json_splited[i])
		if (ft_strwcmp(json_splited[i++], "object:") == 0)
			eng->stats.objects_count++;
	o_array_buffer = (t_object *)ft_memalloc(sizeof(t_object) *
		eng->stats.objects_count);
	i = 0;
	eng->stats.objects_count = 0;
	while (json_splited[i] != NULL)
	{
		splited_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splited_line[0], "object:") == 0)
			util_create_object(eng, &o_array_buffer[eng->stats.objects_count],
			polies_array, splited_line);
		util_release_char_matrix(splited_line);
		i++;
	}
	return (o_array_buffer);
}

t_polygone	*engine_read_polygones_from_file(t_engine *eng,
			t_point_3d *vertex_array, char **json_splited)
{
	t_polygone	*p_array_buffer;
	char		**splited_line;
	int			i;

	i = 0;
	eng->stats.polies_count = 0;
	while (json_splited[i])
		if (ft_strwcmp(json_splited[i++], "polygone:") == 0)
			eng->stats.polies_count++;
	p_array_buffer = (t_polygone *)ft_memalloc(sizeof(t_polygone)
		* eng->stats.polies_count);
	i = 0;
	eng->stats.polies_count = 0;
	while (json_splited[i] != NULL)
	{
		splited_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splited_line[0], "polygone:") == 0)
			util_create_polygone(eng, &p_array_buffer[eng->stats.polies_count],
			vertex_array, splited_line);
		util_release_char_matrix(splited_line);
		i++;
	}
	return (p_array_buffer);
}

t_sector	*engine_read_sectors_from_file(t_engine *eng,
			t_object *objects_array, char **json_splited)
{
	t_sector	*s_array_buffer;
	char		**splited_line;
	int			i;

	i = 0;
	eng->stats.sectors_count = 0;
	while (json_splited[i])
		if (ft_strwcmp(json_splited[i++], "sector:") == 0)
			eng->stats.sectors_count++;
	s_array_buffer = (t_sector *)ft_memalloc(sizeof(t_sector)
		* eng->stats.sectors_count);
	i = 0;
	eng->stats.sectors_count = 0;
	while (json_splited[i] != NULL)
	{
		splited_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splited_line[0], "sector:") == 0)
			util_create_sector(eng, &s_array_buffer[eng->stats.sectors_count],
			objects_array, splited_line);
		util_release_char_matrix(splited_line);
		i++;
	}
	return (s_array_buffer);
}
