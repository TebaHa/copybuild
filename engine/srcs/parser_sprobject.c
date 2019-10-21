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

t_sprobject		*engine_read_sprobjects_from_file(t_engine *eng, t_buff buff)
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
			util_create_sprobject(eng, &sprobject_buff[
				eng->stats.sprobjects_count], &buff, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (sprobject_buff);
}

void			util_create_sprobject(t_engine *eng, t_sprobject *sprobject,
				t_buff *buff, char **str)
{
	util_parsing_error_little_data_check("sprite object", str, 4);
	util_parsing_error_count_handler("sprite object", str, 4);
	util_int10_data_filler(&sprobject->id, str[1], 0, JETPACK);
	util_int10_data_filler(&sprobject->angle, str[2], 0, 360);
	if (ft_atoi(str[3]) < 0 || ft_atoi(str[3]) > ENEMY_NUM)
		util_parsing_error_cant_find("texture from sprobject", ft_atoi(str[3]));
	sprobject->enum_type = ft_atoi(str[3]);
	sprobject->type = eng->enemy[ft_atoi(str[3])];
	sprobject->position = util_get_vertex_from_buff_by_id(ft_atoi(str[4]),
		eng->stats.vertexes_count, buff->vertexes, sprobject->id);
	sprobject->state = E_IDLE;
	sprobject->frame = 0;
	eng->stats.sprobjects_count++;
}

t_sprobject		util_get_sprobject_from_buff_by_id(int id, int size,
				t_sprobject *sprobjects, int sector_id)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (sprobjects[i].id == id)
			break ;
		i++;
	}
	if (i == size)
		util_parsing_error_lost_handler("sprobjects", id, "sector", sector_id);
	return (sprobjects[i]);
}
