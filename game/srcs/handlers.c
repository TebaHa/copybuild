/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 21:34:09 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/06 22:28:09 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

int				rotate_handler(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == TOP_ARROW)
	{
		game->player.px += (int)cos(game->player.angle);
		game->player.py += (int)sin(game->player.angle);
	}
	else if (key == DOWN_ARROW)
	{
		game->player.px -= (int)cos(game->player.angle);
		game->player.py -= (int)sin(game->player.angle);
	}
	else if (key == RIGHT_ARROW)
		game->player.angle += 0.1;
	else if (key == LEFT_ARROW)
		game->player.angle -= 0.1;
	if (key == 53)
		exit(1);
	draw(game);
	return (0);
}
