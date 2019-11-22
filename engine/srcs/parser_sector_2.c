/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sector_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			util_release_sectors_buffer(t_sector *sector_buff, int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		util_release_objects_buffer(sector_buff[i].objects_array,
									sector_buff[i].objects_count);
		i++;
	}
	free(sector_buff);
}

void			util_find_repeats_in_sector(t_sector *sector)
{
	int			j;
	int			i;

	i = 0;
	while (i < sector->objects_count)
	{
		j = 0;
		while (j < sector->objects_count)
		{
			if (i != j &&
				sector->objects_array[i].id == sector->objects_array[j].id)
				util_parsing_error_repeats("objects", "sector", sector->id);
			j++;
		}
		i++;
	}
	util_find_sprobjects_repeats_in_sector(sector);
}
