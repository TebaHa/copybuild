/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 00:57:34 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/04 18:30:03 by fsmith           ###   ########.fr       */
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
	char *config;
	char **splitedconfig;

	config = engine_read_level_file(filename);
	splitedconfig = ft_strsplit(config, '\n');
	eng->world = engine_read_world_from_file(eng, splitedconfig);
	vertex_buff = engine_read_vertexes_from_file(eng, splitedconfig);
	polies_buff = engine_read_polygones_from_file(eng, vertex_buff, splitedconfig);
	object_buff = engine_read_objects_from_file(eng, polies_buff, splitedconfig);
	eng->world->sectors_array = engine_read_sectors_from_file(eng, object_buff, splitedconfig);
	eng->world->renderqueue = (int *)ft_memalloc(sizeof(int) * MAXSECTORS);
	engine_clear_renderstack(eng->world->renderqueue);
	util_release_read_buffers(vertex_buff, polies_buff, object_buff);
	util_release_char_matrix(splitedconfig);
	free(config);
}
