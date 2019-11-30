/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:49:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 16:50:22 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	game_menu_author(t_game *fps)
{
	fps->menu->button[M_PLAY]->active = false;
	fps->menu->button[M_CONTROLS]->active = false;
	fps->menu->button[M_EDITOR]->active = false;
	fps->menu->button[M_AUTHOR]->active = false;
	fps->menu->button[M_EXIT]->active = false;
	fps->menu->button[M_BACK]->active = true;
	fps->menu->element[ME_AUTHORS]->active = true;
	fps->menu->element[ME_ENDGAME]->active = false;
	fps->menu->element[ME_CONTROLS]->active = false;
}

void	game_menu_controls(t_game *fps)
{
	fps->menu->button[M_PLAY]->active = false;
	fps->menu->button[M_CONTROLS]->active = false;
	fps->menu->button[M_EDITOR]->active = false;
	fps->menu->button[M_AUTHOR]->active = false;
	fps->menu->button[M_EXIT]->active = false;
	fps->menu->button[M_BACK]->active = true;
	fps->menu->element[ME_AUTHORS]->active = false;
	fps->menu->element[ME_ENDGAME]->active = false;
	fps->menu->element[ME_CONTROLS]->active = true;
}

void	game_menu_mainframe(t_game *fps)
{
	fps->menu->button[M_PLAY]->active = true;
	fps->menu->button[M_CONTROLS]->active = true;
	fps->menu->button[M_EDITOR]->active = true;
	fps->menu->button[M_AUTHOR]->active = true;
	fps->menu->button[M_EXIT]->active = true;
	fps->menu->button[M_BACK]->active = false;
	fps->menu->element[ME_AUTHORS]->active = false;
	fps->menu->element[ME_ENDGAME]->active = false;
	fps->menu->element[ME_CONTROLS]->active = false;
}

void	game_menu_endgame(t_game *fps)
{
	fps->menu->button[M_PLAY]->active = false;
	fps->menu->button[M_CONTROLS]->active = false;
	fps->menu->button[M_EDITOR]->active = false;
	fps->menu->button[M_AUTHOR]->active = false;
	fps->menu->button[M_EXIT]->active = true;
	fps->menu->button[M_BACK]->active = false;
	fps->menu->element[ME_AUTHORS]->active = false;
	fps->menu->element[ME_ENDGAME]->active = true;
	fps->menu->element[ME_CONTROLS]->active = false;
}
