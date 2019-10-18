/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 01:20:09 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/14 18:09:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			sound_mixer_init(void)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		ft_putendl("Can't initialize SDL audio");
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, SOUNDS_NUM, 4096) == -1)
		ft_putendl("Can't initialize SDL_mixer");
}

Mix_Chunk		*sound_init(char *name)
{
	Mix_Chunk	*sound;
	char		*sound_name;

	sound_name = util_add_wav_to_name(name);
	if (!(sound = Mix_LoadWAV(sound_name)))
	{
		ft_putstr("Can't load ");
		ft_putstr(sound_name);
		ft_putendl("!");
		return (NULL);
	}
	Mix_VolumeChunk(sound, MIX_MAX_VOLUME * GAME_SOUNDS_VOLUME);
	free(sound_name);
	return (sound);
}

void			eng_create_background_music(t_engine *eng)
{
	eng->background_music = sound_init("background_nervous");
	if (Mix_PlayChannel(S_BACKGROUND, eng->background_music, -1) == -1)
		ft_putendl("Background audio play error");
	Mix_VolumeChunk(eng->background_music,
		MIX_MAX_VOLUME * BACKGROUND_MUSIC_VOLUME);
}

void			sound_play(Mix_Chunk *sound_name, t_sound_ch channel)
{
	if (Mix_PlayChannel(channel, sound_name, 0) == -1)
		ft_putendl("Audio play error");
}
