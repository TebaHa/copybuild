/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 21:31:01 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 17:55:09 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	set_flags_editor(t_game *fps)
{
	fps->work.menu = true;
	fps->work.game = false;
	fps->work.editor = false;
}

void	run_controller(t_game *fps)
{
	while (fps->work.work)
	{
		if (fps->work.menu == true)
			game_menu_main(fps);
		else if (fps->work.editor == true)
		{
			run_editor(fps->editor);
			set_flags_editor(fps);
		}
		else if (fps->work.game == true)
		{
			run_game(fps);
			if (fps->eng->ending == true)
			{
				game_end(fps);
				break ;
			}
			fps->work.menu = true;
			fps->work.game = false;
			fps->work.editor = false;
		}
	}
	engine_sdl_uninit(fps->eng);
	close_game(0);
}
