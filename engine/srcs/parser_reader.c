/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/08 20:58:04 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_read_world_from_file(t_engine *eng, char **json_splited)
{
	char	**splitted_line;
	int		i;

	i = 0;
	while (json_splited[i])
	{
		if (ft_strwcmp(json_splited[i], "world:") == 0)
		{
			splitted_line = ft_strsplitwhitespaces(json_splited[i]);
			util_create_world(&eng->world, splitted_line);
			util_release_char_matrix(splitted_line);
		}
		i++;
	}
}

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

t_object	*engine_read_objects_from_file(t_engine *eng,
			t_polygone *polies_array, char **json_splited)
{
	t_object	*o_array_buffer;
	char		**splitted_line;
	int			i;

	o_array_buffer = (t_object *)ft_memalloc(sizeof(t_object) *
		eng->stats.objects_count);
	i = 0;
	eng->stats.objects_count = 0;
	while (json_splited[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splitted_line[0], "object:") == 0)
			util_create_object(eng, &o_array_buffer[eng->stats.objects_count],
			polies_array, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (o_array_buffer);
}

t_polygone	*engine_read_polygones_from_file(t_engine *eng,
			t_point_3d *vertex_array, char **json_splited)
{
	t_polygone	*p_array_buffer;
	char		**splitted_line;
	int			i;

	p_array_buffer = (t_polygone *)ft_memalloc(sizeof(t_polygone)
		* eng->stats.polies_count);
	i = 0;
	eng->stats.polies_count = 0;
	while (json_splited[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splitted_line[0], "polygone:") == 0)
			util_create_polygone(eng, &p_array_buffer[eng->stats.polies_count],
			vertex_array, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (p_array_buffer);
}

void		engine_read_sectors_from_file(t_engine *eng,
			t_object *objects_array, char **json_splited)
{
	char		**splitted_line;
	int			i;

	i = 0;
	eng->stats.sectors_count = 0;
	while (json_splited[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splitted_line[0], "sector:") == 0)
			util_create_sector(eng, &eng->world->sectors_array
			[eng->stats.sectors_count], objects_array, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
}

void		engine_read_worldbox_from_file(t_engine *eng,
			t_object *objects_array, char **json_splited)
{
	char		**splitted_line;
	int			i;

	i = 0;
	while (json_splited[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splitted_line[0], "wrldbx:") == 0)
			util_create_sector(eng, eng->world->world_box,
			objects_array, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
}

t_sprite	*engine_read_sprites_from_file(t_engine *eng,
			t_point_3d *vertex_array, char **json_splited)
{
	t_sprite	*sprites_buff;
	char		**splitted_line;
	int			i;

	sprites_buff = (t_sprite *)ft_memalloc(sizeof(t_sprite) *
					 eng->stats.sprites_count);
	i = 0;
	eng->stats.sprites_count = 0;
	while (json_splited[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splitted_line[0], "sprite:") == 0)
			util_create_sprite(eng, &sprites_buff[eng->stats.sprites_count],
				vertex_array, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (sprites_buff);
}
