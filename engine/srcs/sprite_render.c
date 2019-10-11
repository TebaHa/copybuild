/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 03:13:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/11 13:40:08 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

void		engine_render_sprites(t_engine *eng, t_player *plr, SDL_Surface *surf)
{
	t_item_sprts	*restr;
	t_sector		*sect;

	while (((restr = engine_pop_spriterenderstack(eng->world->sprite_renderqueue)) != NULL))
	{
		sect = eng->world->sectors_array + restr->sect_id.sectorno;
		engine_render_sprites_in_sector(sect, surf, plr, restr);
	}
}

void		engine_render_sprites_in_sector(t_sector *sect, SDL_Surface *surf, t_player *plr, t_item_sprts *restr)
{
	int				i;
	int				j;
	double			planeX;
	double			planey;

	i = 0;
	while (i < sect->sprobjects_count)
	{
		sect->order[i] = i;
		sect->dist[i] = ((plr->position.x - sect->sprobjects_array[i].position.x) * (plr->position.x - sect->sprobjects_array[i].position.x)
		+ (plr->position.y - sect->sprobjects_array[i].position.y) * (plr->position.x  - sect->sprobjects_array[i].position.y));
		i++;
	}
	sprite_comb_sort(sect);
	i = 0;
	while (i < sect->sprobjects_count)
	{
		double dirx, diry;
		double stry, endy;
		double scaledx, scaledy;
		double spritex, spritey;
		spritex = sect->sprobjects_array[sect->order[i]].position.x - plr->position.x;
		spritey = sect->sprobjects_array[sect->order[i]].position.y - plr->position.y;
		dirx = spritex * plr->sinangle - spritey * plr->cosangle;
		diry = spritex * plr->cosangle + spritey * plr->sinangle;
		stry = dirx + (double)sect->sprobjects_array[sect->order[i]].type->anmtn[0]->surface[0]->w / 2.0;
		endy = dirx - (double)sect->sprobjects_array[sect->order[i]].type->anmtn[0]->surface[0]->w / 2.0;
		if (diry <= 0)
		{
			i++;
			continue ;
		}
		scaledx = WIDTH * hfov / diry;
		scaledy = HEIGHT * vfov / diry;
		double x1 = WIDTH / 2 - (int)((stry) * scaledx);
		double x2 = WIDTH / 2 - (int)((endy) * scaledx);
		if (x1 > restr->sect_id.sx2 || x2 < restr->sect_id.sx1)
		{
			i++;
			continue ;
		}
		double ceil = sect->floor + sect->sprobjects_array[sect->order[i]].type->anmtn[0]->surface[0]->h * 2 - plr->position.z;
		double floor = sect->floor - plr->position.z;
		int ya = HEIGHT / 2 - (int)((ceil + diry * plr->yaw) * scaledy);
		int yb = HEIGHT / 2 - (int)((floor + diry * plr->yaw) * scaledy);
		int begx = max(x1, restr->sect_id.sx1);
		int endx = min(x2, restr->sect_id.sx2);
		int x = begx;
		while (x < endx)
		{
			int cya = clamp(ya, restr->ytop[x], restr->ybottom[x]);
			int cyb = clamp(yb, restr->ytop[x], restr->ybottom[x]);
			int txtx = (int)((double)(x - x1) /
						(double)(x2 - x1) * sect->sprobjects_array[sect->order[i]].type->anmtn[0]->surface[0]->w);
			engine_vline_textured_surface(surf, (t_scaler)Scaler_Init(ya, cya, yb, 0, sect->sprobjects_array[sect->order[i]].type->anmtn[0]->surface[0]->h - 1) ,(t_fix_point_3d){x, cya + 1, 0}, (t_fix_point_3d){x, cyb, 0}, txtx, sect->sprobjects_array[sect->order[i]].type->anmtn[0]->surface[0]);
			x++;
		}
		i++;
	}
}