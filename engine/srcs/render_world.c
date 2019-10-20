/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:42:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/19 21:16:01 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int			get_rgb(int r, int g, int b, int a)
{
	return (((((int)r) << 24) & 0xFF000000) |
	((((int)g) << 16) & 0x00FF0000) |
	(((b) << 8) & 0x0000FF00) | (((a)) & 0x000000FF));
}

void		engine_render_world_data(t_player *plr, t_wall_help2 *data)
{
	int		i;

	i = 0;
	data->prev = -1;
	data->plr = plr;
	data->sect = (t_item){plr->cursector, 0, WIDTH - 1};
	while (i < WIDTH)
	{
		data->ytop[i] = 0;
		data->ybottom[i] = HEIGHT;
		i++;
	}
}

void		engine_render_world_help(t_engine *eng, SDL_Surface *surf,
			t_wall_help2 *data)
{
	int		i;

	while (((data->sect = engine_pop_renderstack(
	eng->world->renderstack)).sectorno >= 0))
	{
		i = 0;
		while (i < eng->world->sectors_array[data->sect.sectorno].objects_count)
		{
			data->portal = eng->world->sectors_array
			[data->sect.sectorno].objects_array[i].portal;
			data->polygone = eng->world->sectors_array
			[data->sect.sectorno].objects_array[i].polies_array;
			data->obj_id = i;
			engine_render_wall(eng, surf, data);
			i++;
		}
		data->prev = data->sect.sectorno;
	}
}

void		engine_render_world(t_engine *eng, t_player plr, SDL_Surface *surf)
{
	t_wall_help2 data;

	SDL_LockSurface(surf);
	engine_render_world_data(&plr, &data);
	engine_push_renderstack(eng->world->renderstack, data.sect);
	one_dim_zbuffers_copy(&eng->world->sectors_array[data.sect.sectorno].
	item_sprts, data.ytop, data.ybottom);
	eng->world->sectors_array[data.sect.sectorno].
	item_sprts.sect_id = data.sect;
	engine_push_spriterenderstack(eng->world->sprite_renderstack,
	&eng->world->sectors_array[data.sect.sectorno].item_sprts);
	engine_render_world_help(eng, surf, &data);
	engine_render_sprites(eng, &plr, surf);
	engine_clear_renderstack(eng->world->renderstack);
	engine_clear_spriterenderstack(eng->world->sprite_renderstack);
	SDL_UnlockSurface(surf);
}

void		one_dim_zbuffers_copy(t_item_sprts *sprt, int *ytop, int *ybottom)
{
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		sprt->ytop[i] = ytop[i];
		sprt->ybottom[i] = ybottom[i];
		i++;
	}
}
