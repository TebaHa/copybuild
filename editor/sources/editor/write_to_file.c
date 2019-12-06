/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 11:48:45 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 20:54:41 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		write_world(t_sdl *sdl, int fd)
{
	char	*sectors;
	int		i;

	write(fd, "world:	1	", 9);
	sectors = ft_itoa(sdl->count);
	write(fd, sectors, ft_strlen(sectors));
	write(fd, "	", 1);
	free(sectors);
	i = 0;
	sectors = ft_itoa(i++);
	write(fd, sectors, ft_strlen(sectors));
	free(sectors);
	while (i != sdl->count)
	{
		write(fd, " ", 1);
		sectors = ft_itoa(i++);
		write(fd, sectors, ft_strlen(sectors));
		free(sectors);
	}
	write(fd, "\n", 1);
}

void		write_player(t_sdl *sdl, int fd)
{
	write(fd, "player:	0	2000\n\n", 16);
	write(fd, "vertex:	2000	", 13);
	write_to_file(fd, sdl->char_id, sdl->player->x * 4);
	write(fd, "	", 1);
	write_to_file(fd, sdl->char_id, sdl->player->y * 4);
	write(fd, "	", 1);
	write_to_file(fd, sdl->char_id, sdl->sectors->z);
	write(fd, "\n\n", 2);
}

void		write_sprites(t_sdl *sdl, int fd, int last_id)
{
	t_ed_sprite	*cur_sprite;
	int			id;
	int			i;

	cur_sprite = sdl->sprites;
	id = last_id;
	i = 0;
	while (cur_sprite != NULL)
	{
		write(fd, "sobjct:	", 8);
		write_to_file(fd, sdl->char_id, i++);
		write(fd, "	0	", 3);
		write_to_file(fd, sdl->char_id, cur_sprite->type - 1);
		write(fd, "	", 1);
		write_to_file(fd, sdl->char_id, id++);
		write(fd, "\n", 1);
		cur_sprite = cur_sprite->next;
	}
	write(fd, "\n\n", 2);
}

void		write_sectors(t_sdl *sdl, int fd)
{
	t_ed_sector	*cur_sector;
	int			i;

	cur_sector = sdl->sectors;
	while (cur_sector->next != NULL)
	{
		i = 0;
		write(fd, "sector: ", 8);
		write_to_file(fd, sdl->char_id, cur_sector->num_of_sector);
		write(fd, "	0	675	q_floor_5	q_floor_3	0xFFFFFF	", 36);
		write_to_file(fd, sdl->char_id, cur_sector->total_num_of_obj);
		write(fd, "\t", 1);
		while (i < cur_sector->total_num_of_obj)
		{
			write_to_file(fd, sdl->char_id, sdl->num);
			write(fd, " ", 1);
			i++;
			sdl->num++;
		}
		write(fd, "\n", 1);
		cur_sector = cur_sector->next;
	}
}
