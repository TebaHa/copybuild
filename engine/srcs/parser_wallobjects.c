/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wallobjects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_wobj			*engine_read_wallobjects_from_file(t_engine *eng, t_buff buff)
{
	t_wobj		*wallobject_buff;
	char		**splitted_line;
	int			i;

	wallobject_buff = (t_wobj *)ft_memalloc(sizeof(t_wobj) *
		eng->stats.wallobjects_count);
	i = 0;
	eng->stats.wallobjects_count = 0;
	while (buff.str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
		if (ft_strcmp(splitted_line[0], "wobjct:") == 0)
			util_create_wallobject(eng, &wallobject_buff[
				eng->stats.wallobjects_count], splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (wallobject_buff);
}

void			util_create_wallobject(t_engine *eng, t_wobj *wallobject,
				char **str)
{
	util_parsing_error_little_data_check("wall object", str, 6);
	util_parsing_error_count_handler("wall object", str, 6);
	util_int10_data_filler(&wallobject->id, str[1], 0, 10000);
	wallobject->enum_type = ft_atoi(str[2]);
	wallobject->type = eng->button[wallobject->enum_type];
	util_int10_data_filler(&wallobject->object_id, str[3], 0, 10000);
	util_int10_data_filler(&wallobject->height, str[4], 0, 10000);
	util_int10_data_filler(&wallobject->position, str[5], 0, 100);
	util_int10_data_filler(&wallobject->sector_id, str[6], 0, 10000);
	eng->stats.wallobjects_count++;
}
