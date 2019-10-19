/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_particle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:52:01 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/19 21:14:13 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_particle_links(t_ptcl_r *data, t_ptcl_h *links)
{
	data->obj = links->obj;
	data->plr = links->plr;
	data->sect = links->sect;
}

void		engine_render_particle(t_engine *eng, SDL_Surface *surf,
			t_wallobj *particle, t_ptcl_h links)
{
	t_ptcl_r data;

	engine_render_particle_links(&data, &links);
	engine_render_particle_1(eng, surf, particle, &data);
	if (data.t1.y <= 0 && data.t2.y <= 0)
		return ;
	data.u0 = 0;
	data.u1 = particle->texture->surface[particle->frame_num]->h - 1;
	engine_render_particle_2(eng, surf, particle, &data);
	engine_render_particle_5(eng, surf, particle, &data);
	if (data.x1 >= data.x2 ||
	data.x2 < data.sect.sx1
	|| data.x1 > data.sect.sx2)
		return ;
	engine_render_particle_6(eng, surf, particle, &data);
	while (data.x <= data.endx)
		engine_render_particle_7(eng, surf, particle, &data);
	if (particle->texture->a_state == ANIMATE)
	{
		if (((particle->timer % (particle->texture->frames_delay)) == 0)
		&& (particle->frame_num < particle->texture->frames_num - 1))
			particle->frame_num++;
		else
			particle->timer++;
	}
}

void		engine_render_particle_1(t_engine *eng, SDL_Surface *surf,
			t_wallobj *particle, t_ptcl_r *data)
{
	data->c1.x = particle->a.x - data->plr->position.x;
	data->c1.y = particle->a.y - data->plr->position.y;
	data->c2.x = particle->b.x - data->plr->position.x;
	data->c2.y = particle->b.y - data->plr->position.y;
	data->t1.x = data->c1.x * data->plr->sinangle
	- data->c1.y * data->plr->cosangle;
	data->t1.y = data->c1.x * data->plr->cosangle
	+ data->c1.y * data->plr->sinangle;
	data->t2.x = data->c2.x * data->plr->sinangle
	- data->c2.y * data->plr->cosangle;
	data->t2.y = data->c2.x * data->plr->cosangle
	+ data->c2.y * data->plr->sinangle;
}

void		engine_render_particle_5(t_engine *eng, SDL_Surface *surf,
			t_wallobj *particle, t_ptcl_r *data)
{
	data->xscale1 = (WIDTH * hfov) / data->t1.y;
	data->yscale1 = (HEIGHT * vfov) / data->t1.y;
	data->x1 = WIDTH / 2 + (-data->t1.x * data->xscale1);
	data->xscale2 = (WIDTH * hfov) / data->t2.y;
	data->yscale2 = (HEIGHT * vfov) / data->t2.y;
	data->x2 = WIDTH / 2 + (-data->t2.x * data->xscale2);
}
