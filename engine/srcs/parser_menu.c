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

#include <engine.h>

void		eng_create_menu(t_engine *eng)
{
	eng->menu = (t_menu *)ft_memalloc(sizeof(t_menu));
	eng->menu->active_section = M_NONE;
	eng->menu->position = (t_fix_point_2d){0, 0};
	eng->menu->background = util_create_sprite_by_name(eng, "m_background");
	eng->menu->button[M_STORY] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	eng->menu->button[M_STORY]->position = (t_fix_point_2d){332, 180};
	eng->menu->button[M_STORY]->normal = util_create_sprite_by_name(eng, "m_story_norm");
	eng->menu->button[M_STORY]->active = util_create_sprite_by_name(eng, "m_story_act");
	eng->menu->button[M_LOAD_MAP] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	eng->menu->button[M_LOAD_MAP]->position = (t_fix_point_2d){332, 270};
	eng->menu->button[M_LOAD_MAP]->normal = util_create_sprite_by_name(eng, "m_load_norm");
	eng->menu->button[M_LOAD_MAP]->active = util_create_sprite_by_name(eng, "m_load_act");
	eng->menu->button[M_EDITOR] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	eng->menu->button[M_EDITOR]->position = (t_fix_point_2d){332, 360};
	eng->menu->button[M_EDITOR]->normal = util_create_sprite_by_name(eng, "m_editor_norm");
	eng->menu->button[M_EDITOR]->active = util_create_sprite_by_name(eng, "m_editor_act");
	eng->menu->button[M_AUTHOR] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	eng->menu->button[M_AUTHOR]->position = (t_fix_point_2d){332, 450};
	eng->menu->button[M_AUTHOR]->normal = util_create_sprite_by_name(eng, "m_author_norm");
	eng->menu->button[M_AUTHOR]->active = util_create_sprite_by_name(eng, "m_author_act");
	eng->menu->button[M_EXIT] = (t_menu_button *)ft_memalloc(sizeof(t_menu_button));
	eng->menu->button[M_EXIT]->position = (t_fix_point_2d){332, 540};
	eng->menu->button[M_EXIT]->normal = util_create_sprite_by_name(eng, "m_exit_norm");
	eng->menu->button[M_EXIT]->active = util_create_sprite_by_name(eng, "m_exit_act");
}
