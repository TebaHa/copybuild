/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravitation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:47:20 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/02 00:42:53 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	apply_gravitation(t_game *fps)
{
	if (fps->player.controller.falling == 1 && fps->logic.grav == 1)
	{
		fps->player.position.z -= fps->logic.dz;
		fps->logic.dz += 2;
		if (fps->eng->world->sectors_array[fps->player.cursector].
		floor + 150 - fps->logic.duck_shift >
		fps->player.position.z)
		{
			fps->player.controller.falling = 0;
			fps->player.position.z = fps->eng->world->sectors_array
			[fps->player.cursector].floor + 150 -
			fps->logic.duck_shift;
			fps->logic.dz = 0;
		}
	}
	else
		fps->player.plr_state = P_IDLE;
}
