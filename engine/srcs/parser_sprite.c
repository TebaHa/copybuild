/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_sprite	*util_create_sprite_by_name(t_engine *eng, char *str)
{
	t_sprite *res;

	res = (t_sprite *)ft_memalloc(sizeof(t_sprite));
	res->frames_delay = DEFAULT_SPRITE_DELAY;
	if (util_create_static_sprite(eng, str, res))
		return (res);
	else if (util_create_animated_sprite(eng, str, res))
		return (res);
	res->frames_num = 1;
	res->a_state = STATIC;
	util_parsing_error_no_sprite(res->surface, eng, str);
	res->name = util_add_png_to_name(PARSING_ERROR_SPRITE);
	return (res);
}

void		util_find_sprite_by_name(SDL_Surface **dst, t_engine *eng,
			char *name)
{
	int		i;
	char	*name_png;

	i = 0;
	if (!name)
	{
		*dst = NULL;
		return ;
	}
	name_png = util_add_png_to_name(name);
	while (i < eng->stats.sprites_count)
	{
		if (!ft_strcmp(name_png, eng->sprites_buffer[i]->filename))
		{
			*dst = util_transform_texture_to_sprite(
					&eng->sprites_buffer[i]->texture);
			break ;
		}
		i++;
	}
	free(name_png);
	if (i == eng->stats.sprites_count)
		util_parsing_error_no_sprite(dst, eng, name);
	else
		eng->stats.cycle_detector = 0;
}
