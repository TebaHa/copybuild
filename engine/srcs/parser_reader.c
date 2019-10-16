/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

char		**engine_read_level_file(char *filename)
{
	int			fd;
	int			number;
	char		*buff;
	char		**splitedbuff;

	fd = open(GAME_PATH, O_RDONLY);
	buff = (char*)malloc(sizeof(char) * 10000);
	if (fd < 2)
		util_parsing_error_no_lvl_file(filename);
	number = read(fd, buff, 10000);
	buff[number] = '\0';
	close(fd);
	splitedbuff = ft_strsplit(buff, '\n');
	if (checksum_check(buff, splitedbuff, number) != CRC_OK)
		util_parsing_error_wrong_crc();
	free(buff);
	return (splitedbuff);
}

void		engine_read_world_from_file(t_engine *eng, char **json_splited)
{
	char	**splitted_line;
	int		i;

	i = 0;
	while (json_splited[i])
	{
		splitted_line = ft_strsplitwhitespaces(json_splited[i]);
		if (ft_strcmp(splitted_line[0], "world:") == 0)
			util_create_world(&eng->world, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
}
