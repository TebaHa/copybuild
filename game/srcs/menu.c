/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:49:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/18 22:46:51 by zytrams          ###   ########.fr       */
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
				menu->button[i]->position.x,
				menu->button[i]->position.y);
			else
				draw_from_surface_to_surface(surf,
				menu->button[i]->normal->surface[0],
				menu->button[i]->position.x,
				menu->button[i]->position.y);
		}
		i++;
	}
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

void	game_find_button(t_game *fps)
{
	int	i;

	i = 0;
	fps->menu->mouseover_section = -1;
	while (i < M_SECTIONS_NUM)
	{
		if (check_button(fps->eng->x, fps->eng->y,
		(t_fix_point_2d){fps->menu->button[i]->position.x,
		fps->menu->button[i]->position.y},
		(t_fix_point_2d){fps->menu->button[i]->position.x +
		fps->menu->button[i]->normal->surface[0]->w,
		fps->menu->button[i]->position.y +
		fps->menu->button[i]->normal->surface[0]->h})
		&& fps->menu->button[i]->active)
			fps->menu->mouseover_section = i;
		i++;
	}
}

int		check_button(int x, int y,
		t_fix_point_2d pos_a, t_fix_point_2d pos_b)
{
	if ((x >= pos_a.x && x <= pos_b.x)
	&& (y >= pos_a.y && y <= pos_b.y))
		return (1);
	return (0);
}

int		check_button_pushed(t_game *fps)
{
	if (fps->menu->mouseover_section == M_LOAD_MAP)
		return (1);
	else if (fps->menu->mouseover_section == M_AUTHOR)
		game_menu_author(fps);
	else if (fps->menu->mouseover_section == M_BACK)
		game_menu_mainframe(fps);
	else if (fps->menu->mouseover_section == M_EDITOR)
		return (1);
	else if (fps->menu->mouseover_section == M_EXIT)
		return (1);
	return (0);
}

void	apply_button(t_game *fps)
{
	if (fps->menu->mouseover_section == M_LOAD_MAP)
	{
		fps->work.menu = false;
		fps->work.game = true;
		fps->work.editor = false;
	}
	else if (fps->menu->mouseover_section == M_EDITOR)
	{
		fps->work.editor = true;
		fps->work.game = false;
		fps->work.menu = false;
	}
	else if (fps->menu->mouseover_section == M_EXIT)
		game_quit(fps);
}

void	game_menu_main(t_game *fps)
{
	SDL_ShowCursor(SDL_ENABLE);
	while (fps->work.menu == true)
	{
		SDL_GetMouseState(&fps->eng->x, &fps->eng->y);
		game_find_button(fps);
		game_render_menu(fps->menu, fps->render_thread_pool[0].surface);
		if (SDL_PollEvent(&fps->eng->event))
		{
			if (fps->eng->event.type == SDL_QUIT)
			{
				game_quit(fps);
				break ;
			}
			if (fps->eng->event.type == SDL_KEYDOWN)
			{
				if (fps->eng->event.key.keysym.sym == SDLK_ESCAPE)
				{
					game_quit(fps);
					break ;
				}
			}
			if (fps->eng->event.button.type == SDL_MOUSEBUTTONDOWN)
				if (fps->eng->event.button.button == SDL_BUTTON_LEFT)
					if (check_button_pushed(fps))
						break;
		}
		engine_render_frame(fps->eng,
		fps->render_thread_pool[0].surface);
		engine_present_and_clear_frame(fps->eng);
	}
	apply_button(fps);
}

void 	game_menu_author(t_game *fps)
{
	fps->menu->button[M_STORY]->active = false;
	fps->menu->button[M_LOAD_MAP]->active = false;
	fps->menu->button[M_EDITOR]->active = false;
	fps->menu->button[M_AUTHOR]->active = false;
	fps->menu->button[M_EXIT]->active = false;
	fps->menu->button[M_BACK]->active = true;
	fps->menu->element[ME_AUTHORS]->active = true;
	fps->menu->element[ME_ENDGAME]->active = false;
}

void 	game_menu_mainframe(t_game *fps)
{
	fps->menu->button[M_STORY]->active = true;
	fps->menu->button[M_LOAD_MAP]->active = true;
	fps->menu->button[M_EDITOR]->active = true;
	fps->menu->button[M_AUTHOR]->active = true;
	fps->menu->button[M_EXIT]->active = true;
	fps->menu->button[M_BACK]->active = false;
	fps->menu->element[ME_AUTHORS]->active = false;
	fps->menu->element[ME_ENDGAME]->active = false;
}

void 	game_menu_endgame(t_game *fps)
{
	fps->menu->button[M_STORY]->active = false;
	fps->menu->button[M_LOAD_MAP]->active = false;
	fps->menu->button[M_EDITOR]->active = false;
	fps->menu->button[M_AUTHOR]->active = false;
	fps->menu->button[M_EXIT]->active = true;
	fps->menu->button[M_BACK]->active = false;
	fps->menu->element[ME_AUTHORS]->active = false;
	fps->menu->element[ME_ENDGAME]->active = true;
}
