/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:54:24 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/23 19:44:19 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void 	engine_create_resources_from_file(t_engine *eng)
{
	eng_read_textures(eng);
	eng_read_sprites(eng);
	eng->weapon = (t_weapon *)ft_memalloc(sizeof(t_weapon));
//	eng->weapon->next = eng->weapon;
//	eng->weapon->prev = eng->weapon;
	eng_create_rifle(eng);
//	eng_create_plazma(eng);
	ft_putendl(eng->weapon->anmtn[IDLE]->name);
//	ft_putnbr(eng->weapon->anmtn[IDLE]->frames_num);
//	ft_putendl("!");

}
