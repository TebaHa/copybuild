/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprobject.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_sprobject	*engine_read_sprobjects_from_file(t_engine *eng, t_buff buff)
{
	t_sprobject	*sprobject_buff;
	char		**splitted_line;
	int			i;

	sprobject_buff = (t_sprobject *)ft_memalloc(sizeof(t_sprobject) *
												eng->stats.sprobjects_count);
	i = 0;
	eng->stats.sprobjects_count = 0;
	while (buff.str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
		if (ft_strcmp(splitted_line[0], "sobjct:") == 0)
			util_create_sprobject(eng, &sprobject_buff[eng->stats.sprobjects_count],
								  buff.sprites, buff.vertexes, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (sprobject_buff);
}
