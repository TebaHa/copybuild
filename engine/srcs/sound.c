/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 01:20:09 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/11 01:46:54 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			sound_mixer_init(void)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		ft_putendl("Can't initialize SDL audio");
	if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, SOUNDS_NUM, 4096) == -1 )
		ft_putendl("Can't initialize SDL_mixer");
}

Mix_Chunk		*sound_init(char *name)
{
	Mix_Chunk	*sound = NULL;
	char		*sound_name;

	sound_name = util_add_wav_to_name(name);
	sound = Mix_LoadWAV(sound_name);
	if (sound == NULL)
	{
		ft_putstr("Can't load ");
		ft_putstr(sound_name);
		ft_putendl("!");
	}
	free(sound_name);
	return sound;
}

char		*util_add_wav_to_name(char *old_name)
{
	char	*new_name;
	char	*new_wav_name;

	new_name = ft_strjoin(SOUND_PATH, old_name);
	new_wav_name = ft_strjoin(new_name, ".wav");
	free(new_name);
	return (new_wav_name);
}

void	sound_play(Mix_Chunk *sound_name, t_sound_ch channel)
{
	if (Mix_PlayChannel(channel, sound_name, 0) == -1 )
		ft_putendl("Audio play error");
}

void	sound_free(t_engine *eng)
{
	Mix_FreeChunk(eng->weapon[0]->shot_sound);
//	Mix_FreeChunk(eng->weapon[1]->shot_sound);
	Mix_CloseAudio();
}

void	sound_shoot(t_player *plr)
{
	sound_play(plr->wpn->shot_sound, S_WEAPON_SHOT);
}
