/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render_twalls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:14:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/18 19:13:01 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_render_ts_objects(t_engine *eng, t_surf_and_plr ps,
			t_wall_help2 *data, t_render_stacks *stacks)
{
	t_trns_item		item;
	t_sector		*sect;
	t_sprobject		*aimed;

	eng->aim = NULL;
	while (((item = engine_pop_tsrenderstack(
	stacks->helpstack)).status != 0))
	{
		if (item.sprite_renderstack == NULL)
		{
			data->polygone = item.trnsprtstack.obj->polies_array;
			data->sect.sectorno = item.trnsprtstack.sx->sect_id.sectorno;
			data->color = item.trnsprtstack.color;
			data->sect = item.trnsprtstack.sx->sect_id;
			data->tybottom = item.trnsprtstack.sx->ybottom;
			data->tytop = item.trnsprtstack.sx->ytop;
			engine_render_twall(eng, ps.surf, data, stacks);
		}
		else
		{
			sect = eng->world->sectors_array + item.sprite_renderstack->sect_id.sectorno;
			aimed = engine_render_sprites_in_sector(sect, ps.surf, ps.plr, item.sprite_renderstack);
			if (aimed)
				eng->aim = aimed;
		}
	}
}
