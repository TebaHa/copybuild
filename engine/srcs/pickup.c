/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:49:25 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/12 14:51:42 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

void		check_sprites_in_sector(t_player *plr, t_sector *sect)
{
	int		i;

	i = 0;
	while (i < sect->sprobjects_count)
	{
		check_sprite_pick(plr, &sect->sprobjects_array[i]);
		i++;
	}
}

void		check_sprite_pick(t_player *plr, t_sprobject *sobj)
{
	double	dist;
	double	tmp;

	tmp = pow((plr->position.x - sobj->position.x), 2) + pow((plr->position.y - sobj->position.y), 2);
	printf("tmp %f \n", tmp);
	if (tmp == 0)
		return ;
	dist = sqrt(tmp);
	printf("dist %f \n", dist);
	if (dist <= 20.1)
	{
		sobj->norender = true;
		apply_sprite_obj(plr, sobj);
	}
}

void		apply_sprite_obj(t_player *plr, t_sprobject *sobj)
{
	return ;
}