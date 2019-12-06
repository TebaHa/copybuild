/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect_r.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 09:55:28 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:51:42 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		check_condition_r(t_sdl *sdl, t_ed_sector *sector, int count)
{
	if (sector->rh / sector->cmn >= 0 && sector->rh / sector->cmn <= 1 &&
			sector->sh / sector->cmn >= 0 && sector->sh / sector->cmn <= 1)
		count = count_intersection(sdl, sector, count);
	return (count);
}

void	find_intersection_r(t_ed_sector *sector, int i, int x2, int y2)
{
	sector->rh = (YO - sector->point[i + 1].y) *
			(sector->point[i].x - sector->point[i + 1].x) -
			(X1 - sector->point[i + 1].x) *
			(sector->point[i].y - sector->point[i + 1].y);
	sector->sh = (YO - sector->point[i + 1].y) * (x2 - X1) -
			(X1 - sector->point[i + 1].x) * (y2 - YO);
}

void	calculate_cmn_r(t_ed_sector *sector, int i, int x2, int y2)
{
	sector->cmn = (x2 - X1) * (sector->point[i].y - sector->point[i + 1].y) -
		(y2 - YO) * (sector->point[i].x - sector->point[i + 1].x);
}

int		cond_r(t_sdl *sdl, t_ed_sector *head)
{
	if ((head->num_of_sector != -1 && head->check == 0) ||
			(sdl->is_overlay == 0 && head->check == 0))
		return (1);
	return (0);
}

int		check_intersect_r(t_sdl *sdl, t_ed_sector *head, int x2, int y2)
{
	int		i;
	int		count;

	count = 0;
	while (head != NULL)
	{
		i = 0;
		if (cond_r(sdl, head) == 1)
		{
			while (i + 1 < head->size)
			{
				calculate_cmn_r(head, i, x2, y2);
				if (head->cmn == 0)
				{
					i++;
					continue ;
				}
				find_intersection_r(head, i, x2, y2);
				count = check_condition_r(sdl, head, count);
				i++;
			}
		}
		head = head->next;
	}
	return (count);
}
