/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render_twall_main2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:03:19 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 13:38:15 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			engine_set_tlinks(t_wall_clinks *links, void *ls[6])
{
	links->cycler = (t_wall_cycle *)ls[0];
	links->data = (t_wall_help2 *)ls[1];
	links->data_help = (t_wall_help3 *)ls[2];
	links->eng = (t_engine *)ls[3];
	links->mdata = (t_wall_mai_data *)ls[4];
	links->surf = (SDL_Surface *)ls[5];
}

void			engine_render_twall_main_cycler(t_wall_clinks *l,
				t_wall_cycle *cycler, t_wall_mai_data *mdata)
{
	while (cycler->x <= mdata->endx)
	{
		l->mdata->txtx = (l->data_help->u0 * ((l->mdata->x2 - l->cycler->x)
		* l->data_help->t2.y) + l->data_help->u1
		* ((l->cycler->x - l->mdata->x1) * l->data_help->t1.y))
		/ ((l->mdata->x2 - l->cycler->x) * l->data_help->t2.y + (l->cycler->x
		- l->mdata->x1) * l->data_help->t1.y);
		l->mdata->ya = scaler_next(&l->mdata->ya_int);
		l->mdata->yb = scaler_next(&l->mdata->yb_int);
		if (l->mdata->ya == l->mdata->yb)
			return ;
		l->mdata->cya = clamp(l->mdata->ya, l->data->tytop[l->cycler->x],
		l->data->tybottom[l->cycler->x]);
		l->mdata->cyb = clamp(l->mdata->yb, l->data->tytop[l->cycler->x],
		l->data->tybottom[l->cycler->x]);
		engine_render_twall_cycle(l);
		++cycler->x;
	}
}
