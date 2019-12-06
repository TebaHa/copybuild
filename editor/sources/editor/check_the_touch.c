/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the_touch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:49:10 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:51:54 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** (x1, y1, x2, y2, x3, y3)
** (x1, y1, x2, y2, x4, y4)
** (x3, y3, x4, y4, x1, y1)
** (x3, y3, x4, y4, x2, y2)
**
** int x1 = cur_wall->x1;
** int y1 = cur_wall->y1;
** int x2 = cur_wall->x2;
** int y2 = cur_wall->y2;
** int x3 = cur_wall->neighbour_x1 = head->point[j].x;
** int y3 = cur_wall->neighbour_y1 = head->point[j - 1].y;
** int x4 = cur_wall->neighbour_x2 = head->point[j].x;
** int y4 = cur_wall->neighbour_y2 = head->point[j].y;
*/

int		check_segments(t_walls *wall, t_walls *checkwall)
{
	if (((wall->x1 == checkwall->x2 &&
			wall->y1 == checkwall->y2) &&
			(wall->x2 == checkwall->x1 &&
			wall->y2 == checkwall->y1)) ||
			((wall->x1 == checkwall->x1 &&
			wall->y1 == checkwall->y1) &&
			(wall->x2 == checkwall->x2 &&
			wall->y2 == checkwall->y2)))
		return (1);
	return (0);
}

void	check_the_touch(t_ed_sector *cur_sector, int num, t_ed_sector *head)
{
	int	j;

	while (head != NULL)
	{
		j = 0;
		while (j < head->num_of_walls)
		{
			if (cur_sector->num_of_sector != head->num_of_sector)
			{
				if (check_segments(&cur_sector->walls[num],
									&head->walls[j]) == 1)
					cur_sector->walls[num].portal = head->num_of_sector;
			}
			j++;
		}
		head = head->next;
	}
}

void	find_portals(t_sdl *sdl)
{
	t_ed_sector	*cur_sector;
	t_ed_sector	*head;
	int			i;

	cur_sector = sdl->sectors;
	head = sdl->sectors;
	while (cur_sector->next != NULL)
	{
		i = 0;
		while (i < cur_sector->num_of_walls)
		{
			check_the_touch(cur_sector, i, head);
			i++;
		}
		cur_sector = cur_sector->next;
	}
}
