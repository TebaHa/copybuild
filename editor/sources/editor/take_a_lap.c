/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_a_lap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:46:30 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 20:53:09 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	add_point(t_sdl *sdl, t_ed_sector *sector, int i)
{
	sector->point[sector->size].x = sdl->grid_field[i].x;
	sector->point[sector->size].y = sdl->grid_field[i].y;
	if (sector->size > 0)
		save_wall(sector, sector->size);
	sector->size++;
	add_command(sdl, &(sdl->commands), WALL_TYPE);
}

void	check_wall(t_walls *walls, t_ed_sector *sector, t_ed_point *grid_field)
{
	walls->x1 = sector->point[sector->size - 2].x;
	walls->y1 = sector->point[sector->size - 2].y;
	walls->x2 = sector->point[sector->size - 1].x;
	walls->y2 = sector->point[sector->size - 1].y;
	walls->neighbour_x1 = grid_field->x;
	walls->neighbour_y1 = grid_field->y;
}

int		check_point(t_ed_sector *head, int num_of_sector, int x, int y)
{
	int	i;

	while (head != NULL)
	{
		i = 0;
		if (num_of_sector != head->num_of_sector)
		{
			while (i < head->size)
			{
				if (head->point[i].x == x && head->point[i].y == y)
				{
					return (1);
				}
				i++;
			}
		}
		head = head->next;
	}
	return (0);
}

int		checks(t_sdl *sdl, t_ed_sector *sector, int i)
{
	if ((check_intersect_l(sdl, sdl->sectors, sdl->grid_field[i].x,
			sdl->grid_field[i].y) % 2 == 0 &&
			check_intersect_r(sdl, sdl->sectors, sdl->grid_field[i].x,
			sdl->grid_field[i].y) % 2 == 0) ||
			(check_intersect_l(sdl, sdl->sectors, sdl->grid_field[i].x,
			sdl->grid_field[i].y) % 2 == 1 &&
			check_point(sdl->sectors, sector->num_of_sector,
			sdl->grid_field[i].x, sdl->grid_field[i].y) == 1) ||
			(check_intersect_r(sdl, sdl->sectors, sdl->grid_field[i].x,
			sdl->grid_field[i].y) % 2 == 1 &&
			check_point(sdl->sectors, sector->num_of_sector,
			sdl->grid_field[i].x, sdl->grid_field[i].y) == 1))
		return (1);
	return (0);
}

void	make_wall(t_sdl *sdl)
{
	int			i;
	t_ed_sector	*sector;
	t_walls		*walls;

	walls = (t_walls *)malloc(sizeof(t_walls));
	sector = get_last_sector(sdl->sectors);
	if (sdl->save_click == 0)
	{
		if (sector == NULL)
		{
			sdl->sectors = init_sector();
			sector = sdl->sectors;
		}
		SDL_GetMouseState(&sdl->mouse_position.x, &sdl->mouse_position.y);
		if ((i = check_the_grid(sdl->grid_field, sdl->mouse_position.x,
								sdl->mouse_position.y)) >= 0)
		{
			if (sector->size > 1)
				check_wall(walls, sector, &sdl->grid_field[i]);
			if (checks(sdl, sector, i) == 1)
				which_of_points(sdl, sector, walls, i);
		}
	}
	free(walls);
}
