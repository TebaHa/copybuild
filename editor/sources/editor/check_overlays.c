/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_overlays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 09:51:37 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:51:50 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		num_of_the_same_portals(t_ed_sector *cur_sector, t_ed_sector *head)
{
	int	count;
	int num;

	count = 0;
	num = 0;
	if (cur_sector->num_of_sector != head->num_of_sector)
	{
		while (num < cur_sector->num_of_walls)
		{
			if (cur_sector->walls[num].portal > -1 &&
					cur_sector->walls[num].portal == head->num_of_sector)
				count++;
			num++;
		}
	}
	return (count);
}

int		check_doubleport(t_sdl *sdl)
{
	t_ed_sector	*cur_sector;
	t_ed_sector	*head;

	sdl->is_doubleport = 0;
	cur_sector = sdl->sectors;
	while (cur_sector->next != NULL)
	{
		head = sdl->sectors;
		while (head->next != NULL)
		{
			if (num_of_the_same_portals(cur_sector, head) > 1)
			{
				sdl->is_doubleport = 1;
				return (1);
			}
			head = head->next;
		}
		cur_sector = cur_sector->next;
	}
	return (0);
}

int		check_overlays(t_sdl *sdl)
{
	int			i;
	t_ed_sector	*cur_sector;

	sdl->is_overlay = 0;
	cur_sector = sdl->sectors;
	while (cur_sector != NULL)
	{
		i = 0;
		cur_sector->check = 1;
		while (i < cur_sector->size)
		{
			if (check_intersect_l(sdl, sdl->sectors, cur_sector->point[i].x,
					cur_sector->point[i].y) % 2 == 1 &&
					check_intersect_r(sdl, sdl->sectors, cur_sector->point[i].x,
					cur_sector->point[i].y) % 2 == 1 &&
					check_point(sdl->sectors, cur_sector->num_of_sector,
					cur_sector->point[i].x, cur_sector->point[i].y) == 0)
				return (1);
			i++;
		}
		cur_sector->check = 0;
		cur_sector = cur_sector->next;
	}
	return (0);
}
