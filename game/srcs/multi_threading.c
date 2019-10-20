/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:10:20 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/20 21:52:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

int			game_thread_wrapper(void *ptr)
{
	t_game	*fps;

	fps = (t_game *)ptr;
	engine_render_world(fps->eng, fps->player,
	fps->render_thread_pool[fps->thread_num].surface);
	return (fps->thread_num);
}

void		game_init_threads(t_thread_pool *render_thread_pool)
{
	int		i;

	i = 0;
	while (i < THREAD_POOL_SIZE)
	{
		render_thread_pool[i].surface = SDL_CreateRGBSurface(0,
		WIDTH, HEIGHT, 32, (unsigned int)0xff000000,
		(unsigned int)0x00ff0000, (unsigned int)0x0000ff00,
		(unsigned int)0x000000ff);
		i++;
	}
}

void		game_stop_threads(t_thread_pool *render_thread, int thread_count)
{
	int		i;

	i = 0;
	while (i < thread_count)
	{
		SDL_WaitThread(render_thread[i].thread, &render_thread[i].value);
		i++;
	}
}

void		game_threads_recount(t_game *fps)
{
	if (fps->logic.thread_start_index == (THREAD_POOL_SIZE - 1)
	|| fps->logic.init == 1)
	{
		SDL_WaitThread(fps->render_thread_pool
		[fps->logic.thread_end_index].thread,
		&fps->render_thread_pool[fps->logic.thread_end_index].value);
		engine_draw_hud(&fps->player,
		fps->render_thread_pool[fps->logic.thread_end_index].surface);
		engine_render_frame(fps->eng,
		fps->render_thread_pool[fps->logic.thread_end_index].surface);
		engine_render_hud_stats(fps->eng, &fps->player);
		engine_present_and_clear_frame(fps->eng);
		fps->logic.thread_start_index = fps->logic.thread_end_index;
		fps->logic.thread_end_index = fps->logic.thread_end_index
		< (THREAD_POOL_SIZE - 1) ? fps->logic.thread_end_index + 1 : 0;
		if (fps->logic.init == 0)
			fps->logic.init = 1;
	}
	else
		fps->logic.thread_start_index++;
}
