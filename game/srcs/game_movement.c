/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:26:29 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/15 17:47:17 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	game_movement_check(t_game *fps)
{
	fps->thread_num = fps->logic.thread_start_index;
	fps->render_thread_pool[fps->logic.thread_start_index].
	thread = SDL_CreateThread(game_thread_wrapper, NULL, (void *)fps);
	if (fps->player.controller.moving)
	{
		fps->logic.px = fps->player.position.x;
		fps->logic.py = fps->player.position.y;
		fps->logic.dx = fps->player.velocity.x;
		fps->logic.dy = fps->player.velocity.y;
		fps->logic.sectprev = fps->player.cursector;
		check_wall_passed(fps->eng, &fps->player,
		(t_line_2d){(t_point_2d){fps->logic.px, fps->logic.py},
		(t_point_2d){fps->logic.px + fps->logic.dx,
		fps->logic.py + fps->logic.dy}},
		&fps->player.controller.moving);
		fps->logic.sectprev = engine_object_get_sector(fps->eng->world,
		(t_point_3d){0.f, fps->player.position.x
		+ fps->player.velocity.x,
		fps->player.position.y
		+ fps->player.velocity.y, fps->player.position.z},
		fps->player.cursector);
		if (fps->logic.sectprev >= 0 && fps->logic.sectprev
		== fps->player.cursector &&
		fps->eng->world->sectors_array
		[fps->player.cursector].opening.closed == false)
		{
			move_player(fps->eng, &fps->player,
			(t_point_2d){fps->player.velocity.x,
			fps->player.velocity.y});
		}
	}
	if (fps->player.position.z > fps->eng->world->sectors_array
	[fps->player.cursector].floor + fps->logic.duck_shift + 150
	|| fps->player.position.z < fps->eng->world->sectors_array
	[fps->player.cursector].floor + fps->logic.duck_shift + 140)
		fps->player.controller.falling = 1;
}

void	game_apply_movement_main(t_game *fps)
{
	get_relative_xy(fps->eng, &fps->logic.xy);
	fps->player.angle += fps->logic.xy.x * 0.03f;
	fps->logic.yaw = clamp(fps->logic.yaw - fps->logic.xy.y * 0.03f, -3, 3);
	fps->player.yaw = fps->logic.yaw - fps->player.velocity.z * 0.5f;
	move_player(fps->eng, &fps->player,
	(t_point_2d){0, 0});
	fps->logic.move_vec[0] = 0.f;
	fps->logic.move_vec[1] = 0.f;
	game_apply_movement_main_count1(fps);
	game_apply_movement_main_count2(fps);
	fps->logic.pushing = fps->player.controller.wasd[0] ||
	fps->player.controller.wasd[1] || fps->player.controller.wasd[2]
	|| fps->player.controller.wasd[3];
	fps->logic.acceleration = fps->logic.pushing ? 0.4 : 0.2;
	fps->player.velocity.x = fps->player.velocity.x
	* (1 - fps->logic.acceleration) + fps->logic.move_vec[0]
	* fps->logic.acceleration;
	fps->player.velocity.y = fps->player.velocity.y
	* (1 - fps->logic.acceleration) + fps->logic.move_vec[1]
	* fps->logic.acceleration;
	if (fps->logic.pushing)
		fps->player.controller.moving = 1;
	else
		fps->player.controller.moving = 0;
}

void	game_apply_movement_main_count1(t_game *fps)
{
	if (fps->player.controller.wasd[0])
	{
		fps->logic.move_vec[0] += fps->player.cosangle
		* fps->player.controller.running;
		fps->logic.move_vec[1] += fps->player.sinangle
		* fps->player.controller.running;
	}
	if (fps->player.controller.wasd[1])
	{
		fps->logic.move_vec[0] -= fps->player.sinangle
		* fps->player.controller.running;
		fps->logic.move_vec[1] += fps->player.cosangle
		* fps->player.controller.running;
	}
}

void	game_apply_movement_main_count2(t_game *fps)
{
	if (fps->player.controller.wasd[2])
	{
		fps->logic.move_vec[0] += fps->player.sinangle
		* fps->player.controller.running;
		fps->logic.move_vec[1] -= fps->player.cosangle
		* fps->player.controller.running;
	}
	if (fps->player.controller.wasd[3])
	{
		fps->logic.move_vec[0] -= fps->player.cosangle
		* fps->player.controller.running;
		fps->logic.move_vec[1] -= fps->player.sinangle
		* fps->player.controller.running;
	}
}
