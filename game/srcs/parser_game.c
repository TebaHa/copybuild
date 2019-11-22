/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 00:57:34 by fsmith            #+#    #+#             */
/*   Updated: 2019/11/02 02:05:23 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		parser_game(t_game *fps, int argc, char **argv)
{
	parser_filename(fps->eng, argc, argv);
	game_create_resources_from_file(fps);
}

void		game_create_resources_from_file(t_game *fps)
{
	eng_read_sprite(fps->eng, &fps->eng->texture_buffer,
		&fps->eng->stats.textures_count, TEXTURE_PACK_PATH);
	eng_read_sprite(fps->eng, &fps->eng->sprites_buffer,
		&fps->eng->stats.sprites_count, TEXTURE_SPRITE_PATH);
	eng_create_menu(fps);
}
