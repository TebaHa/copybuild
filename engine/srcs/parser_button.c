/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:44:08 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/20 22:56:41 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			eng_create_buttons(t_engine *eng)
{
	eng_create_button_door(eng);
	eng_create_button_finish(eng);
	eng_create_button_reset(eng);
}

void			eng_create_button_door(t_engine *eng)
{
	t_button	*button;

	button = (t_button *)ft_memalloc(sizeof(t_button));
	button->id = BT_DOOR;
	button->name = ft_strdup("Door button");
	button->anmtn[BS_INACTIVE] = util_create_sprite_by_name(eng, "q_button_1_unavaliable");
	button->anmtn[BS_ACTIVE] = util_create_sprite_by_name(eng, "q_button_1_avaliable");
	button->anmtn[BS_PUSHED] = util_create_sprite_by_name(eng, "q_button_1_pressed");
	eng->button[BT_DOOR] = button;
}

void			eng_create_button_finish(t_engine *eng)
{
	t_button	*button;

	button = (t_button *)ft_memalloc(sizeof(t_button));
	button->id = BT_FINISH;
	button->name = ft_strdup("Door button");
	button->anmtn[BS_INACTIVE] = util_create_sprite_by_name(eng, "q_button_2_unavaliable");
	button->anmtn[BS_ACTIVE] = util_create_sprite_by_name(eng, "q_button_2_avaliable");
	button->anmtn[BS_PUSHED] = util_create_sprite_by_name(eng, "q_button_2_pressed");
	eng->button[BT_FINISH] = button;
}

void			eng_create_button_reset(t_engine *eng)
{
	t_button	*button;

	button = (t_button *)ft_memalloc(sizeof(t_button));
	button->id = BUTTON_NUM;
	button->name = ft_strdup("Door button");
	button->anmtn[BS_INACTIVE] = util_create_sprite_by_name(eng, "q_button_1_unavaliable");
	button->anmtn[BS_ACTIVE] = util_create_sprite_by_name(eng, "q_button_1_avaliable");
	button->anmtn[BS_PUSHED] = util_create_sprite_by_name(eng, "q_button_1_pressed");
	eng->button[BT_RESET] = button;
}
