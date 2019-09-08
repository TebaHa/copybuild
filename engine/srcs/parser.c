/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 00:57:34 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/08 20:53:26 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

char		**engine_read_level_file(char *filename)
{
	int			fd;
	int			number;
	char		*buff;
	char		**splitedbuff;

	fd = open(filename, O_RDONLY);
	buff = (char*)malloc(sizeof(char) * 10000);
	if (fd < 2)
		exit(99);
	number = read(fd, buff, 10000);
	buff[number] = '\0';
	close(fd);
	splitedbuff = ft_strsplit(buff, '\n');
	free(buff);
	return (splitedbuff);
}

void		engine_create_world_from_file(t_engine *eng, char *filename)
{
	t_point_3d	*vertex_buff;
	t_polygone	*polies_buff;
	t_object	*object_buff;
	t_sprite	*sprites_buff;
	char		**config;

	config = engine_read_level_file(filename);
	engine_count_all_from_file(eng, config);
	engine_read_world_from_file(eng, config);
	vertex_buff = engine_read_vertexes_from_file(eng, config);
	polies_buff = engine_read_polygones_from_file(eng, vertex_buff, config);
	object_buff = engine_read_objects_from_file(eng, polies_buff, config);
//	sprites_buff = engine_read_sprites_from_file(eng, vertex_buff, config);
	engine_read_sectors_from_file(eng, object_buff, config);
	engine_read_worldbox_from_file(eng, object_buff, config);
	util_release_read_buffers(vertex_buff, polies_buff, object_buff);
	util_release_char_matrix(config);
}

void		engine_count_all_from_file(t_engine *eng, char **json_splited)
{
	int		i;

	i = 0;
	eng->stats.vertexes_count = 0;
	eng->stats.polies_count = 0;
	eng->stats.objects_count = 0;
	eng->stats.sectors_count = 0;
	while (json_splited[i])
	{
		if (ft_strwcmp(json_splited[i], "vertex:") == 0)
			eng->stats.vertexes_count++;
		else if (ft_strwcmp(json_splited[i], "polygone:") == 0)
			eng->stats.polies_count++;
		else if (ft_strwcmp(json_splited[i], "object:") == 0)
			eng->stats.objects_count++;
		else if (ft_strwcmp(json_splited[i], "sector:") == 0)
			eng->stats.sectors_count++;
		else if (ft_strwcmp(json_splited[i], "sprite:") == 0)
			eng->stats.sprites_count++;
		else if (ft_strwcmp(json_splited[i], "sobjct:") == 0)
			eng->stats.sprobjects_count++;
		i++;
	}
}
