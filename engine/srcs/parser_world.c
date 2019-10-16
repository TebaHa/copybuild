/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:12:50 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 19:07:36 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_read_world_from_file(t_engine *eng, char **line)
{
	char	**splitted_line;
	int		i;

	i = 0;
	while (line[i])
	{
		splitted_line = ft_strsplitwhitespaces(line[i]);
		if (ft_strcmp(splitted_line[0], "world:") == 0)
			util_create_world(&eng->world, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
}

void		util_create_world(t_world **world, char **str)
{
	*world = (t_world *)ft_memalloc(sizeof(t_world));
	util_int10_data_filler(&(*world)->id, str[1]);
	util_int10_data_filler(&(*world)->sectors_count, str[2]);
	if (!(*world)->sectors_count)
		util_parsing_error_little_data("sectors", "world", str);
	util_parsing_error_count_handler("world", str, 2 + (*world)->sectors_count);
	(*world)->renderstack = (t_item *)ft_memalloc(sizeof(t_item) * MAXSECTORS);
	(*world)->sectors_array = (t_sector *)ft_memalloc(sizeof(t_sector)
		* (*world)->sectors_count);
	(*world)->world_box = (t_sector *)ft_memalloc(sizeof(t_sector));
	(*world)->sprite_renderstack =
		(t_item_sprts **)ft_memalloc(sizeof(t_item_sprts *) * MAXSECTORS);
	engine_clear_renderstack((*world)->renderstack);
	engine_clear_spriterenderstack((*world)->sprite_renderstack);
}
