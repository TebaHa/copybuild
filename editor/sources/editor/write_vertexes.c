/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_vertexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:19:28 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 20:54:44 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		write_wall_string(int fd, char *char_id, int id, t_ed_point *point)
{
	write(fd, "vertex:	", 8);
	write_to_file(fd, char_id, id);
	write(fd, "	", 1);
	write_to_file(fd, char_id, point->x * 4);
	write(fd, "	", 1);
	write_to_file(fd, char_id, point->y * 4);
	write(fd, "	", 1);
}

int			write_vertexes_wall(t_sdl *sdl, int fd)
{
	t_ed_sector	*cur_sector;
	int			i;
	int			id;

	cur_sector = sdl->sectors;
	id = 0;
	while (cur_sector != NULL && cur_sector->size != 0)
	{
		i = 0;
		while (i != cur_sector->size)
		{
			write_wall_string(fd, sdl->char_id, id++, &cur_sector->point[i]);
			write_to_file(fd, sdl->char_id, cur_sector->z);
			write(fd, "\n", 1);
			i++;
		}
		write(fd, "\n", 1);
		cur_sector = cur_sector->next;
	}
	return (id);
}

void		write_vertexes_sprite(t_sdl *sdl, int fd, int last_id)
{
	t_ed_sprite	*cur_sprite;
	int			id;

	cur_sprite = sdl->sprites;
	id = last_id;
	while (cur_sprite != NULL)
	{
		write(fd, "vertex:	", 8);
		write_to_file(fd, sdl->char_id, id++);
		write(fd, "	", 1);
		write_to_file(fd, sdl->char_id, cur_sprite->x * 4);
		write(fd, "	", 1);
		write_to_file(fd, sdl->char_id, cur_sprite->y * 4);
		write(fd, "	", 1);
		write_to_file(fd, sdl->char_id, sdl->sectors->z);
		write(fd, "\n", 1);
		cur_sprite = cur_sprite->next;
	}
	write(fd, "\n\n", 2);
}
