/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:28:56 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/06 22:01:01 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void		init_player(t_player *player, long x, long y, long angle)
{
	player->angle = angle;
	player->px = x;
	player->py = y;
}

void		draw(t_game *fps)
{
	ft_bzero(fps->eng->img.ptr_data, fps->eng->img.width * fps->eng->img.height * 4);
	draw_player(&fps->eng->img, fps->player.px, fps->player.py, fps->player.angle);
	draw_map(&fps->eng->img, &fps->eng->portals);
	mlx_put_image_to_window(fps->eng->window.ptr_mlx, fps->eng->window.ptr_window, fps->eng->img.ptr_img, 0, 0);
}

int			main(void)
{
	t_game	fps;

	init_player(&fps.player, 125, 125, 0);
	fps.eng = init_engine();
	draw(&fps);
	mlx_key_hook(fps.eng->window.ptr_window, rotate_handler, &fps);
	mlx_loop(fps.eng->window.ptr_mlx);
}
