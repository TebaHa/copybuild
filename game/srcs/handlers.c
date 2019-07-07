/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 21:34:09 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/07 21:02:21 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

int				rotate_handler(int key, void *param)
{
	t_game	*game;
	double	angle;

	game = (t_game *)param;
	angle = game->player.angle * M_PI / 180.0;
	if (key == TOP_ARROW)
	{
		game->player.px += cos(angle) * 5;
		game->player.py += sin(angle) * 5;
	}
	else if (key == DOWN_ARROW)
	{
		game->player.px -= cos(angle) * 5;
		game->player.py -= sin(angle) * 5;
	}
	else if (key == RIGHT_ARROW)
		game->player.angle += 1;
	else if (key == LEFT_ARROW)
		game->player.angle -= 1;
	if (key == TWO_DIM_KEY)
		game->eng->view_type = TWODIM;
	else if (key == THREE_DIM_KEY)
		game->eng->view_type = THREEDIM;
	if (key == 53)
		exit(1);
	draw(game);
	return (0);
}
