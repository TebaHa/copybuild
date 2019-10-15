/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:54:24 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/15 20:09:11 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void 	engine_create_resources_from_file(t_engine *eng)
{
	eng_read_sprite(eng, &eng->texture_buffer,
	&eng->stats.textures_count, TEXTURE_PACK_PATH);
	eng_read_sprite(eng, &eng->sprites_buffer,
	&eng->stats.sprites_count, TEXTURE_SPRITE_PATH);
	eng_create_hud(eng);
	eng_create_weapons(eng);
	eng_create_items(eng);
	eng_create_enemies(eng);
	eng_create_background_music(eng);
}

void	eng_create_background_music(t_engine *eng)
{
//	eng->background_music = sound_init("background_helpless");
	eng->background_music = sound_init("background_nervous");
	if (Mix_PlayChannel(S_BACKGROUND, eng->background_music, -1) == -1 )
		ft_putendl("Background audio play error");
	Mix_VolumeChunk(eng->background_music, MIX_MAX_VOLUME * BACKGROUND_MUSIC_VOLUME);
}
