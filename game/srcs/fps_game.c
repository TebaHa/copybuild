/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:28:56 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/07 21:02:54 by zytrams          ###   ########.fr       */
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
	if (fps->eng->view_type == TWODIM)
	{
		draw_player_2d(&fps->eng->img, 0, 0, fps->player.angle);
		draw_map_2d(&fps->eng->img, &fps->eng->portals, &fps->player);
	}
	else
	{
		draw_map_3d(&fps->eng->img, &fps->eng->portals, &fps->player);
	}
	mlx_put_image_to_window(fps->eng->window.ptr_mlx, fps->eng->window.ptr_window, fps->eng->img.ptr_img, 0, 0);
}

int			main(void)
{
	t_game	fps;

	init_player(&fps.player, 0, 0, 0);
	fps.eng = init_engine();
	draw(&fps);
	mlx_key_hook(fps.eng->window.ptr_window, rotate_handler, &fps);
	mlx_loop(fps.eng->window.ptr_mlx);
}
