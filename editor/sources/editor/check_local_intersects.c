/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_local_intersects.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:13:35 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:51:45 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		count_intersection(t_sdl *sdl, t_ed_sector *head, int count)
{
	count++;
	if (count % 2 == 1 && sdl->type_pressed == SPRITE_TYPE)
		sdl->sprite_in_sector = head->num_of_sector;
	return (count);
}

void	find_local_intersection(t_ed_sector *head, int i, t_walls *wall)
{
	head->rh = (wall->neighbour_y1 - head->point[i + 1].y) *
			(head->point[i].x - head->point[i + 1].x) -
			(wall->neighbour_x1 - head->point[i + 1].x) *
			(head->point[i].y - head->point[i + 1].y);
	head->sh = (wall->neighbour_y1 - head->point[i + 1].y) *
			(wall->x2 - wall->neighbour_x1) - (wall->neighbour_x1 -
			head->point[i + 1].x) * (wall->y2 - wall->neighbour_y1);
}

int		check_local_intersection(t_sdl *sdl, t_ed_sector *cur_sect,
		t_walls *wall)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (i + 1 < cur_sect->size)
	{
		cur_sect->cmn = (wall->x2 - wall->neighbour_x1) *
				(cur_sect->point[i].y - cur_sect->point[i + 1].y) -
				(wall->y2 - wall->neighbour_y1) * (cur_sect->point[i].x -
				cur_sect->point[i + 1].x);
		if (cur_sect->cmn == 0)
		{
			i++;
			continue ;
		}
		find_local_intersection(cur_sect, i, wall);
		if (cur_sect->rh / cur_sect->cmn >= 0 &&
				cur_sect->rh / cur_sect->cmn <= 1 &&
				cur_sect->sh / cur_sect->cmn >= 0 &&
				cur_sect->sh / cur_sect->cmn <= 1)
			count = count_intersection(sdl, cur_sect, count);
		i++;
	}
	return (count);
}
