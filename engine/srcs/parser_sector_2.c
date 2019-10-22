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

void		util_check_sprobject_in_sector(t_engine *eng, t_buff buff)
{
	int		sprobj_count;
	int		sect_count;

	sect_count = 0;
	while (sect_count < eng->stats.sectors_count)
	{
		sprobj_count = 0;
		while (sprobj_count < buff.sectors[sect_count].sprobjects_count)
		{
			if (engine_object_get_sector(eng->world,
			buff.sectors[sect_count].sprobjects_array[sprobj_count].position,
			buff.sectors[sect_count].id) != buff.sectors[sect_count].id)
			{
				ft_putstr("Parsing error:\nSprobject ");
				ft_putnbr(buff.sectors[sect_count].
				sprobjects_array[sprobj_count].id);
				ft_putstr(" not in sector ");
				ft_putnbr(buff.sectors[sect_count].id);
				ft_putstr("!\n");
				close_game(PARSING_ERROR);
			}
			sprobj_count++;
		}
		sect_count++;
	}
}
