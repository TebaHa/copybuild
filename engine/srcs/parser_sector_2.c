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

void		util_release_sectors_buffer(t_sector *sector_buff, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		util_release_objects_buffer(sector_buff[i].objects_array,
									sector_buff[i].objects_count);
		i++;
	}
	free(sector_buff);
}
