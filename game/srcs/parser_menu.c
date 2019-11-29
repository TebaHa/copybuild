/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:37:20 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/29 17:06:43 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		eng_create_menu(t_game *fps)
{
	if ((fps->menu = (t_menu *)ft_memalloc(sizeof(t_menu))) == NULL)
		util_malloc_error("menu");
	fps->menu->mouseover_section = M_NONE;
	fps->menu->position = (t_fix_point_2d){0, 0};
	fps->menu->background =
			util_create_sprite_by_name(fps->eng, "m_background");
	if ((fps->menu->element[ME_AUTHORS] =
	(t_menu_element *)ft_memalloc(sizeof(t_menu_element))) == NULL)
		util_malloc_error("menu authors");
	fps->menu->element[ME_AUTHORS]->position = (t_fix_point_2d){332, 180};
	fps->menu->element[ME_AUTHORS]->sprite =
			util_create_sprite_by_name(fps->eng, "m_authors");
	fps->menu->element[ME_AUTHORS]->active = false;
	if ((fps->menu->element[ME_ENDGAME] =
	(t_menu_element *)ft_memalloc(sizeof(t_menu_element))) == NULL)
		util_malloc_error("menu endgame");
	fps->menu->element[ME_ENDGAME]->position = (t_fix_point_2d){332, 180};
	fps->menu->element[ME_ENDGAME]->sprite =
			util_create_sprite_by_name(fps->eng, "m_endgame");
	fps->menu->element[ME_ENDGAME]->active = false;
	eng_create_menu_2(fps);
	eng_create_menu_3(fps);
	eng_create_menu_4(fps);
}

void		eng_create_menu_2(t_game *fps)
{
	if ((fps->menu->element[ME_CONTROLS] =
	(t_menu_element *)ft_memalloc(sizeof(t_menu_element))) == NULL)
		util_malloc_error("menu controls");
	fps->menu->element[ME_CONTROLS]->position = (t_fix_point_2d){332, 180};
	fps->menu->element[ME_CONTROLS]->sprite =
			util_create_sprite_by_name(fps->eng, "m_controls");
	fps->menu->element[ME_CONTROLS]->active = false;
	if ((fps->menu->button[M_PLAY] =
	(t_menu_button *)ft_memalloc(sizeof(t_menu_button))) == NULL)
		util_malloc_error("button play");
	fps->menu->button[M_PLAY]->position = (t_fix_point_2d){332, 180};
	fps->menu->button[M_PLAY]->normal =
			util_create_sprite_by_name(fps->eng, "m_play_norm");
	fps->menu->button[M_PLAY]->mouseover =
			util_create_sprite_by_name(fps->eng, "m_play_act");
	fps->menu->button[M_PLAY]->active = true;
	if ((fps->menu->button[M_CONTROLS] =
	(t_menu_button *)ft_memalloc(sizeof(t_menu_button))) == NULL)
		util_malloc_error("button controls");
	fps->menu->button[M_CONTROLS]->position = (t_fix_point_2d){332, 270};
	fps->menu->button[M_CONTROLS]->normal =
			util_create_sprite_by_name(fps->eng, "m_controls_norm");
	fps->menu->button[M_CONTROLS]->mouseover =
			util_create_sprite_by_name(fps->eng, "m_controls_act");
	fps->menu->button[M_CONTROLS]->active = true;
}

void		eng_create_menu_3(t_game *fps)
{
	if ((fps->menu->button[M_EDITOR] =
	(t_menu_button *)ft_memalloc(sizeof(t_menu_button))) == NULL)
		util_malloc_error("button editor");
	fps->menu->button[M_EDITOR]->position = (t_fix_point_2d){332, 360};
	fps->menu->button[M_EDITOR]->normal =
			util_create_sprite_by_name(fps->eng, "m_editor_norm");
	fps->menu->button[M_EDITOR]->mouseover =
			util_create_sprite_by_name(fps->eng, "m_editor_act");
	fps->menu->button[M_EDITOR]->active = true;
	if ((fps->menu->button[M_AUTHOR] =
	(t_menu_button *)ft_memalloc(sizeof(t_menu_button))) == NULL)
		util_malloc_error("button author");
	fps->menu->button[M_AUTHOR]->position = (t_fix_point_2d){332, 450};
	fps->menu->button[M_AUTHOR]->normal =
			util_create_sprite_by_name(fps->eng, "m_author_norm");
	fps->menu->button[M_AUTHOR]->mouseover =
			util_create_sprite_by_name(fps->eng, "m_author_act");
	fps->menu->button[M_AUTHOR]->active = true;
}

void		eng_create_menu_4(t_game *fps)
{
	if ((fps->menu->button[M_EXIT] =
	(t_menu_button *)ft_memalloc(sizeof(t_menu_button))) == NULL)
		util_malloc_error("button exit");
	fps->menu->button[M_EXIT]->position = (t_fix_point_2d){332, 540};
	fps->menu->button[M_EXIT]->normal =
			util_create_sprite_by_name(fps->eng, "m_exit_norm");
	fps->menu->button[M_EXIT]->mouseover =
			util_create_sprite_by_name(fps->eng, "m_exit_act");
	fps->menu->button[M_EXIT]->active = true;
	if ((fps->menu->button[M_BACK] =
	(t_menu_button *)ft_memalloc(sizeof(t_menu_button))) == NULL)
		util_malloc_error("button back");
	fps->menu->button[M_BACK]->position = (t_fix_point_2d){332, 540};
	fps->menu->button[M_BACK]->normal =
			util_create_sprite_by_name(fps->eng, "m_back_norm");
	fps->menu->button[M_BACK]->mouseover =
			util_create_sprite_by_name(fps->eng, "m_back_act");
	fps->menu->button[M_BACK]->active = false;
}
