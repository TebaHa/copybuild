/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:54:24 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/28 13:50:10 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void 	engine_create_resources_from_file(t_engine *eng)
{
	eng_read_textures(eng);
	eng_read_sprites(eng);
	eng_create_rifle(eng);
	eng_create_plasma(eng);
	eng_create_medkit(eng);
	eng_create_armor(eng);
	eng_create_powerup(eng);
	eng_create_rifle_ammo(eng);
	eng_create_plasma_ammo(eng);
	eng_create_plasma_gun(eng);
	eng_create_barrel(eng);
	eng_create_afrit(eng);
	eng_create_cacodemon(eng);
	eng_create_imp(eng);
}