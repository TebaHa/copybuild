/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 00:57:34 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/20 14:46:09 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

char		*engine_read_level_file(char *filename)
{
	int			fd;
	int			number;
	char		*buff;

	fd = open(filename, O_RDONLY);
	buff = (char*)malloc(sizeof(char) * 10000);
	if (fd < 2)
		exit(99);
	number = read(fd, buff, 10000);
	buff[number] = '\0';
	close(fd);
	return (buff);
}

void		engine_create_world_from_file(t_engine *eng, char *filename)
{
	t_point_3d	*vertex_buff;
	t_polygone	*polies_buff;
	t_object	*object_buff;

	char *config = engine_read_level_file(filename);
	char **splitedconfig = ft_strsplit(config, '\n');
	eng->world = engine_read_world_from_file(eng, splitedconfig);
	vertex_buff = engine_read_vertexes_from_file(eng, splitedconfig);
	polies_buff = engine_read_polygones_from_file(eng, vertex_buff, splitedconfig);
	object_buff = engine_read_objects_from_file(eng, polies_buff, splitedconfig);
	eng->world->sectors_array = engine_read_sectors_from_file(eng, object_buff, splitedconfig);
	eng->world->sectors_count = eng->stats.sectors_count;
	eng->world->renderqueue = (t_item *)ft_memalloc(sizeof(t_item) * MAXSECTORS);
	engine_clear_renderstack(eng->world->renderqueue);
	util_release_read_buffers(vertex_buff, polies_buff, object_buff);
	util_release_char_matrix(splitedconfig);
	free(config);
}

t_world		*engine_read_world_from_file(t_engine *eng, char **json_splited)
{
	t_world	*res_world;
	int		i;
	char	**splited_line;

	i = 0;
	while (json_splited[i])
	{
		if (json_splited[i][0] != '#')
		{
			splited_line = ft_strsplit(json_splited[i], ' ');
			if (ft_strcmp(splited_line[0], "world:") == 0)
				res_world = util_create_world(ft_atoi(splited_line[1]), ft_atoi(splited_line[2]));
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	return (res_world);
}

t_point_3d	*engine_read_vertexes_from_file(t_engine *eng, char **json_splited)
{
	t_point_3d	*buff_array;
	int			i;
	int			size;
	char		**splited_line;

	i = 0;
	size = 0;
	while (json_splited[i] != NULL)
	{
		if (json_splited[i][0] != '#')
		{
			splited_line = ft_strsplit(json_splited[i], ' ');
			if (ft_strcmp(splited_line[0], "vertex:") == 0)
				size++;
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	i = 0;
	eng->stats.vertexes_count = size;
	buff_array = (t_point_3d *)ft_memalloc(sizeof(t_point_3d) * size);
	size = 0;
	while (json_splited[i])
	{
		if (json_splited[i][0] != '#')
		{
			splited_line = ft_strsplit(json_splited[i], ' ');
			if (ft_strcmp(splited_line[0], "vertex:") == 0)
				buff_array[size++] = (t_point_3d){ft_atoi(splited_line[1]), ft_atoi(splited_line[2]), ft_atoi(splited_line[3]), ft_atoi(splited_line[4])};
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	return (buff_array);
}

t_object	*engine_read_objects_from_file(t_engine *eng, t_polygone *polies_array, char **json_splited)
{
	t_object	*o_array_buffer;
	int			i;
	int			j;
	int			tmp;
	int			size;
	char		**splited_line;

	i = 0;
	size = 0;
	while (json_splited[i])
	{
		if (json_splited[i][0] != '#')
		{
			splited_line = ft_strsplit(json_splited[i], ' ');
			if (ft_strcmp(splited_line[0], "object:") == 0)
				size++;
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	i = 0;
	o_array_buffer = (t_object *)ft_memalloc(sizeof(t_object) * size);
	eng->stats.objects_count = size;
	size = 0;
	while (json_splited[i] != NULL)
	{
		if (json_splited[i][0] != '#')
		{
			splited_line = ft_strsplit(json_splited[i], ' ');
			if (ft_strcmp(splited_line[0], "object:") == 0)
			{
				o_array_buffer[size].id = ft_atoi(splited_line[1]);
				o_array_buffer[size].portal = ft_atoi(splited_line[2]);
				o_array_buffer[size].polies_count = ft_atoi(splited_line[3]);
				o_array_buffer[size].polies_array = (t_polygone *)ft_memalloc(sizeof(t_polygone) * o_array_buffer[size].polies_count);
				tmp = 4;
				j = 0;
				while (tmp < 4 + o_array_buffer[size].polies_count)
					o_array_buffer[size].polies_array[j++] = util_get_polygone_from_buff_by_id(ft_atoi(splited_line[tmp++]),
											eng->stats.polies_count, polies_array);
				size++;
			}
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	return (o_array_buffer);
}

t_polygone	*engine_read_polygones_from_file(t_engine *eng, t_point_3d *vertex_array, char **json_splited)
{
	t_polygone	*p_array_buffer;
	int			i;
	int			j;
	int			tmp;
	int			size;
	char		**splited_line;

	i = 0;
	size = 0;
	while (json_splited[i])
	{
		if (json_splited[i][0] != '#')
		{
			splited_line = ft_strsplit(json_splited[i], ' ');
			if (ft_strcmp(splited_line[0], "polygone:") == 0)
				size++;
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	i = 0;
	p_array_buffer = (t_polygone *)ft_memalloc(sizeof(t_polygone) * size);
	eng->stats.polies_count = size;
	size = 0;
	while (json_splited[i] != NULL)
	{
		if (json_splited[i][0] != '#')
		{
			splited_line = ft_strsplit(json_splited[i], ' ');
			if (ft_strcmp(splited_line[0], "polygone:") == 0)
			{
				p_array_buffer[size].id = ft_atoi(splited_line[1]);
				p_array_buffer[size].type = ft_atoi(splited_line[2]);
				p_array_buffer[size].color = ft_atoi(splited_line[3]);
				p_array_buffer[size].vertices_count = ft_atoi(splited_line[4]);
				p_array_buffer[size].vertices_array = (t_point_3d *)ft_memalloc(sizeof(t_point_3d) * p_array_buffer[size].vertices_count);
				tmp = 5;
				j = 0;
				while (tmp < 5 + p_array_buffer[size].vertices_count)
					p_array_buffer[size].vertices_array[j++] = util_get_vertex_from_buff_by_id(ft_atoi(splited_line[tmp++]),
											eng->stats.vertexes_count, vertex_array);
				size++;
			}
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	return (p_array_buffer);
}

t_sector	*engine_read_sectors_from_file(t_engine *eng, t_object *sector_array, char **json_splited)
{
	t_sector	*s_array_buffer;
	int			i;
	int			j;
	int			tmp;
	int			size;
	char		**splited_line;

	i = 0;
	size = 0;
	while (json_splited[i])
	{
		if (json_splited[i][0] != '#')
		{
			splited_line = ft_strsplit(json_splited[i], ' ');
			if (ft_strcmp(splited_line[0], "sector:") == 0)
				size++;
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	i = 0;
	s_array_buffer = (t_sector *)ft_memalloc(sizeof(t_sector) * size);
	eng->stats.sectors_count = size;
	size = 0;
	while (json_splited[i] != NULL)
	{
		if (json_splited[i][0] != '#')
		{
			splited_line = ft_strsplit(json_splited[i], ' ');
			if (ft_strcmp(splited_line[0], "sector:") == 0)
			{
				s_array_buffer[size].id = ft_atoi(splited_line[1]);
				s_array_buffer[size].floor = ft_atoi(splited_line[2]);
				s_array_buffer[size].ceil = ft_atoi(splited_line[3]);
				s_array_buffer[size].objects_count = ft_atoi(splited_line[4]);
				s_array_buffer[size].objects_array = (t_object *)ft_memalloc(sizeof(t_object) * s_array_buffer[size].objects_count);
				tmp = 5;
				j = 0;
				while (tmp < 5 + s_array_buffer[size].objects_count)
					s_array_buffer[size].objects_array[j++] = util_get_object_from_buff_by_id(ft_atoi(splited_line[tmp++]),
											eng->stats.objects_count, sector_array);
				size++;
			}
			util_release_char_matrix(splited_line);
		}
		i++;
	}
	return (s_array_buffer);
}
