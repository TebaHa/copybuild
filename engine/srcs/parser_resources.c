/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:54:24 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/08 21:20:07 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void 	engine_create_resources_from_file(t_engine *eng)
{
	eng_read_textures(eng);
	eng_read_sprites(eng);
	eng_create_hud(eng);
	eng_create_weapons(eng);
	eng_create_items(eng);
	eng_create_enemies(eng);
}
