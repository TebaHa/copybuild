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
				eng->stats.wallobjects_count], &buff, splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (wallobject_buff);
}

void			util_create_wallobject(t_engine *eng, t_wobj *wallobject,
				t_buff *buff, char **str)
{
	int 		i;

	util_parsing_error_little_data_check("wall object", str, 6);
	util_parsing_error_count_handler("wall object", str, 6);
	util_int10_data_filler(&wallobject->id, str[1], 0, 10000);
	wallobject->enum_type = ft_atoi(str[2]);
	wallobject->type = eng->button[wallobject->enum_type];
	util_int10_data_filler(&wallobject->object_id, str[3], 0, 10000);
	i = 0;
	while (i < eng->stats.objects_count)
	{
		if (buff->objects[i].id == wallobject->object_id)
		{
			buff->objects[i].wallobjects_num++;
			break ;
		}
		i++;
	}
	if (i == eng->stats.objects_count)
		util_parsing_error_lost_handler("object", wallobject->object_id, "wall object", wallobject->id);
//	i = 0;
//	while (i < eng->stats.sectors_count)
//	{
//		if (buff->sectors[i].id == wallobject->sector_id)
//			break ;
//		i++;
//	}
//	if (i == eng->stats.sectors_count)
//		util_parsing_error_lost_handler("sector", wallobject->sector_id, "wall object", wallobject->id);
	util_int10_data_filler(&wallobject->height, str[4], 0, 10000);
	util_int10_data_filler(&wallobject->position, str[5], 0, 100);
	util_int10_data_filler(&wallobject->sector_id, str[6], 0, 10000);
	eng->stats.wallobjects_count++;
}

//t_wobj			util_get_wallobject_from_buff_by_object_id(int object_id, int size,
//				t_wobj *objects)
//{
//	int			i;
//
//
//	i = 0;
//	while (i < size)
//	{
//		if (objects[i].id == id)
//			break ;
//		i++;
//	}
//	if (i == size)
//		util_parsing_error_lost_handler("object", id, "sector", sector_id);
//	return (objects[i]);
//}
//
//void			util_add_wobjs_to_objects(t_engine *eng, t_buff *buff)
//{
//	int 		i;
//
//	i = 0;
//	while (i < eng->stats.objects_count)
//	{
//		if (buff->objects[i].wallobjects_num)
//		{
//			buff->objects[i].wallobjects_array = (t_wobj *)ft_memalloc(sizeof(t_wobj) *
//				buff->objects[i].wallobjects_num);
//			buff->objects[i].wallobjects_array =
//				util_get_wallobject_from_buff_by_object_id(i, eng->stats.wallobjects_count, buff->wallobjects);
//		}
//		i++;
//	}
//}
