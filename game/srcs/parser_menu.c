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
	fps->menu = (t_menu *)ft_memalloc(sizeof(t_menu));
	fps->menu->active_section = M_NONE;
	fps->menu->position = (t_fix_point_2d){0, 0};
	fps->menu->background = util_create_sprite_by_name(fps->eng, "m_background");
	fps->menu->button[M_STORY] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	fps->menu->button[M_STORY]->position = (t_fix_point_2d){332, 180};
	fps->menu->button[M_STORY]->normal = util_create_sprite_by_name(fps->eng, "m_story_norm");
	fps->menu->button[M_STORY]->active = util_create_sprite_by_name(fps->eng, "m_story_act");
	fps->menu->button[M_LOAD_MAP] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	fps->menu->button[M_LOAD_MAP]->position = (t_fix_point_2d){332, 270};
	fps->menu->button[M_LOAD_MAP]->normal = util_create_sprite_by_name(fps->eng, "m_load_norm");
	fps->menu->button[M_LOAD_MAP]->active = util_create_sprite_by_name(fps->eng, "m_load_act");
	fps->menu->button[M_EDITOR] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	fps->menu->button[M_EDITOR]->position = (t_fix_point_2d){332, 360};
	fps->menu->button[M_EDITOR]->normal = util_create_sprite_by_name(fps->eng, "m_editor_norm");
	fps->menu->button[M_EDITOR]->active = util_create_sprite_by_name(fps->eng, "m_editor_act");
	fps->menu->button[M_AUTHOR] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	fps->menu->button[M_AUTHOR]->position = (t_fix_point_2d){332, 450};
	fps->menu->button[M_AUTHOR]->normal = util_create_sprite_by_name(fps->eng, "m_author_norm");
	fps->menu->button[M_AUTHOR]->active = util_create_sprite_by_name(fps->eng, "m_author_act");
	fps->menu->button[M_EXIT] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	fps->menu->button[M_EXIT]->position = (t_fix_point_2d){332, 540};
	fps->menu->button[M_EXIT]->normal = util_create_sprite_by_name(fps->eng, "m_exit_norm");
	fps->menu->button[M_EXIT]->active = util_create_sprite_by_name(fps->eng, "m_exit_act");
}
