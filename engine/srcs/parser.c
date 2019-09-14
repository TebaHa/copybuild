/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 00:57:34 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/14 16:21:03 by fsmith           ###   ########.fr       */
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
	t_buff		buff;

	buff.str = engine_read_level_file(filename);
	engine_count_all_from_file(eng, buff.str);
	engine_read_world_from_file(eng, buff.str);
	buff.vertexes = engine_read_vertexes_from_file(eng, buff.str);
	buff.sprites = engine_read_sprites_from_file(eng, buff);
	buff.polies = engine_read_polygones_from_file(eng, buff);
	buff.objects = engine_read_objects_from_file(eng, buff);
	buff.sprobjects = engine_read_sprobjects_from_file(eng, buff);
	engine_read_sectors_from_file(eng, buff);
	engine_read_worldbox_from_file(eng, buff);
	util_release_read_buffers(&buff);
	ft_putendl("PARSING OK!");
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
			eng->stats.skins_count++;
		else if (ft_strwcmp(json_splited[i], "sobjct:") == 0)
			eng->stats.sprobjects_count++;
		i++;
	}
}

void		util_release_read_buffers(t_buff *buff)
{
	free(buff->vertexes);
	free(buff->polies);
	free(buff->objects);
	free(buff->sprobjects);
	free(buff->sprites);
	util_release_char_matrix(buff->str);
}
