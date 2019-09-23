/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:54:24 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/23 21:40:50 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void 	engine_create_resources_from_file(t_engine *eng)
{
	eng_read_textures(eng);
	eng_read_sprites(eng);
	eng_create_rifle(eng);
	eng_create_plasma(eng);
	eng->enemy = (t_enemy **)ft_memalloc(sizeof(t_enemy *) * ENEMY_NUM);
	eng_create_barrel(eng);
	eng_create_afrit(eng);
//	ft_putnbr(eng->weapon->anmtn[IDLE]->frames_num);
	ft_putendl("!");
}
