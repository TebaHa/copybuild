/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/20 19:36:54 by zytrams          ###   ########.fr       */
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
	buff = (char*)malloc(sizeof(char) * 50000);
	if (fd < 2)
		util_parsing_error_no_lvl_file(filename);
	number = read(fd, buff, 50000);
	buff[number] = '\0';
	close(fd);
	splitedbuff = ft_strsplit(buff, '\n');
	free(buff);
	return (splitedbuff);
}

void		util_parsing_error_no_lvl_file(char *problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Can't find ");
	ft_putstr(problem);
	ft_putstr("!\n");
	close_game(PARSING_ERROR);
}
