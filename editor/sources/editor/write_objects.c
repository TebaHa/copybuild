/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:04:24 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:53:16 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		write_obj_string(int fd, char *char_id, int id, t_walls *wall)
{
	write_to_file(fd, char_id, wall->portal);
	write(fd, "	", 1);
	if (wall->portal > -1)
		write(fd, "	1	1	null		flooring	ceiling	", 28);
	else
		write(fd, "	0	1	q_bricks_2	flooring	ceiling	", 33);
	write_to_file(fd, char_id, id);
	write(fd, " ", 1);
	write_to_file(fd, char_id, id + 1);
	write(fd, "\n", 1);
}

void		write_objects(t_sdl *sdl, int fd)
{
	t_ed_sector	*cur_sector;
	int			i;
	int			count;

	cur_sector = sdl->sectors;
	count = 0;
	while (cur_sector != NULL)
	{
		i = 0;
		cur_sector->total_num_of_obj = 0;
		while (i < cur_sector->size - 1)
		{
			write(fd, "object:	", 8);
			write_to_file(fd, sdl->char_id, count);
			write(fd, "	", 1);
			write_obj_string(fd, sdl->char_id, sdl->id, &cur_sector->walls[i]);
			sdl->id++;
			cur_sector->total_num_of_obj++;
			i++;
			count++;
		}
		write(fd, "\n", 1);
		sdl->id++;
		cur_sector = cur_sector->next;
	}
}
