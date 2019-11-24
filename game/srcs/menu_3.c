/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:49:39 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 14:11:09 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	game_render_menu(t_menu *menu, SDL_Surface *surf)
{
	int	i;

	i = 0;
	draw_from_surface_to_surface(surf, menu->background->surface[0], 0, 0);
	while (i < M_SECTIONS_NUM)
	{
		if (menu->button[i]->active)
		{
			if (menu->mouseover_section == i)
				draw_from_surface_to_surface(surf,
				menu->button[i]->mouseover->surface[0],
				menu->button[i]->position.x, menu->button[i]->position.y);
			else
				draw_from_surface_to_surface(surf,
				menu->button[i]->normal->surface[0],
				menu->button[i]->position.x, menu->button[i]->position.y);
		}
		i++;
	}
	game_render_menu_help(menu, surf);
}

void	game_render_menu_help(t_menu *menu, SDL_Surface *surf)
{
	int	i;

	i = 0;
	while (i < ME_ELEMENTS_NUM)
	{
		if (menu->element[i]->active)
			draw_from_surface_to_surface(surf,
			menu->element[i]->sprite->surface[0],
			menu->element[i]->position.x,
			menu->element[i]->position.y);
		i++;
	}
}

int		game_menu_break_check(t_game *fps)
{
	if (fps->eng->event.type == SDL_QUIT)
	{
		game_quit(fps);
		return (0);
	}
	if (fps->eng->event.type == SDL_KEYDOWN)
	{
		if (fps->eng->event.key.keysym.sym == SDLK_ESCAPE)
		{
			game_quit(fps);
			return (0);
		}
	}
	if (fps->eng->event.button.type == SDL_MOUSEBUTTONDOWN)
		if (fps->eng->event.button.button == SDL_BUTTON_LEFT)
			if (check_button_pushed(fps))
				return (0);
	return (1);
}
