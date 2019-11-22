/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 22:49:32 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/22 20:17:46 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_put_text(t_engine *eng, t_player *plr)
{
	if (plr->costil != NULL)
	{
		eng->str_info = plr->costil;
		eng->text_time = plr->text_time;
		plr->costil = NULL;
		plr->text_time = 0;
	}
}

void	engine_replace_text(t_player *plr, char *str)
{
	if (plr->costil != NULL)
		free(plr->costil);
	plr->costil = ft_strdup(str);
	plr->text_time = TEXT_TIME;
}

void	engine_check_text(t_engine *eng)
{
	if (eng->text_time == 0)
	{
		free(eng->str_info);
		eng->str_info = NULL;
	}
	eng->text_time--;
}

void	engine_render_text(t_engine *eng, t_player *plr)
{
	SDL_Surface		*txt;

	engine_put_text(eng, plr);
	if (eng->str_info)
	{
		txt = create_text(eng, eng->str_info, 0xFFFFFFFF);
		if (txt)
			draw_player_stats(eng, txt, (t_point_2d){80, 10});
	}
	engine_check_text(eng);
}
