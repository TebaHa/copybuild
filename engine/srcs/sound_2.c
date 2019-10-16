/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 01:20:09 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/14 18:09:14 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		sound_shoot(t_player *plr)
{
	if (!Mix_Playing(S_WEAPON_SHOT))
		sound_play(plr->wpn->shot_sound, S_WEAPON_SHOT);
}

void		sound_player_control(t_player *plr)
{
	if (plr->controller.moving && !Mix_Playing(S_PLAYER))
	{
		Mix_HaltChannel(S_PLAYER);
		sound_play(plr->steps_sound, S_PLAYER);
	}
	else if (!plr->controller.moving && Mix_Playing(S_PLAYER))
		Mix_HaltChannel(S_PLAYER);
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
