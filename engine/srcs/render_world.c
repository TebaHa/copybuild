/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:42:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 15:25:31 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int			get_rgb(int r, int g, int b, int a)
{
	return (((((int)r) << 24) & 0xFF000000) |
	((((int)g) << 16) & 0x00FF0000) |
	((((int)b) << 8) & 0x0000FF00) | (((a)) & 0x000000FF));
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
			t_wall_help2 *data, t_render_stacks *stacks)
{
	int		i;

	while (((data->sect = engine_pop_renderstack(
	stacks->renderstack)).sectorno >= 0))
	{
		i = 0;
		while (i < eng->world->sectors_array[data->sect.sectorno].objects_count)
		{
			data->portal = eng->world->sectors_array
			[data->sect.sectorno].objects_array[i].portal;
			data->polygone = eng->world->sectors_array
			[data->sect.sectorno].objects_array[i].polies_array;
			data->obj_id = i;
			engine_render_wall(eng, surf, data, stacks);
			i++;
		}
	}
}

void		sprt_first_push(t_render_stacks *stacks, t_item_sprts *sptrs)
{
	t_trns_item		trs_item;

	trs_item.sprite_renderstack = sptrs;
	engine_push_tsrenderstack(stacks->helpstack,
	trs_item);
}

void		engine_render_world(t_engine *eng, t_player plr,
			SDL_Surface *surf, t_render_stacks *stacks)
{
	t_wall_help2	data;
	t_surf_and_plr	ps;

	SDL_LockSurface(surf);
	ps.plr = &plr;
	ps.surf = surf;
	engine_draw_background(eng, surf, plr.yaw, plr.angle);
	engine_render_world_data(&plr, &data);
	engine_push_renderstack(stacks->renderstack, data.sect);
	one_dim_zbuffers_copy(&eng->world->sectors_array[data.sect.sectorno].
	item_sprts, data.ytop, data.ybottom);
	eng->world->sectors_array[data.sect.sectorno].
	item_sprts.sect_id = data.sect;
	data.rendered = stacks->rendered;
	data.rendered[plr.cursector] = 1;
	sprt_first_push(stacks,
	&eng->world->sectors_array[data.sect.sectorno].item_sprts);
	engine_render_world_help(eng, surf, &data, stacks);
	engine_render_ts_objects(eng, ps, &data, stacks);
	engine_clear_renderstack(stacks->renderstack);
	engine_clear_tsrenderstack(stacks->helpstack);
	ft_bzero(stacks->rendered, eng->stats.sectors_count);
	SDL_UnlockSurface(surf);
}
