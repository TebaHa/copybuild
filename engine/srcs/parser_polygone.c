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

t_polygone	*engine_read_polygones_from_file(t_engine *eng, t_buff buff)
{
	t_polygone	*p_array_buffer;
	char		**splitted_line;
	int			i;

	p_array_buffer = (t_polygone *)ft_memalloc(sizeof(t_polygone)
											   * eng->stats.polies_count);
	i = 0;
	eng->stats.polies_count = 0;
	while (buff.str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
		if (ft_strcmp(splitted_line[0], "polygone:") == 0)
			util_create_polygone(eng, &p_array_buffer[eng->stats.polies_count],
								 buff.vertexes, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (p_array_buffer);
}
