/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int			util_create_static_sprite(t_engine *eng, char *str, t_sprite *res)
{
	int		i;

	i = 0;
	res->name = util_add_png_to_name(str);
	while (i < eng->stats.sprites_count)
	{
		if (!ft_strcmp(res->name, eng->sprites_buffer[i]->filename))
		{
			res->frames_num = 1;
			res->a_state = STATIC;
			if ((res->surface = (SDL_Surface **)
			ft_memalloc(sizeof(SDL_Surface *))) == NULL)
				util_malloc_error("surface");
			res->surface[0] = util_transform_texture_to_sprite(
					&eng->sprites_buffer[i]->texture);
			break ;
		}
		i++;
	}
	if (i < eng->stats.sprites_count)
		return (1);
	return (0);
}

int			util_count_frames(t_engine *eng, char *str)
{
	int		i;
	int		srfc_count;
	char	*name;

	i = 0;
	srfc_count = 0;
	while (i != eng->stats.sprites_count)
	{
		name = util_add_png_num_to_name(str, srfc_count + 1);
		while (i < eng->stats.sprites_count)
		{
			if (!ft_strcmp(name, eng->sprites_buffer[i]->filename))
			{
				srfc_count++;
				free(name);
				i = 0;
				break ;
			}
			i++;
		}
	}
	if (name)
		free(name);
	return (srfc_count);
}

void		util_create_animated_sprite2(t_engine *eng, char *str,
			t_sprite *res, int *srfc_count)
{
	int		i;
	char	*name;

	name = util_add_png_num_to_name(str, *srfc_count + 1);
	i = 0;
	while (i < eng->stats.sprites_count)
	{
		if (!ft_strcmp(name, eng->sprites_buffer[i]->filename))
		{
			res->surface[*srfc_count] =
				util_transform_texture_to_sprite(
				&eng->sprites_buffer[i]->texture);
			*srfc_count += 1;
			free(name);
			break ;
		}
		i++;
	}
}

int			util_create_animated_sprite(t_engine *eng, char *str, t_sprite *res)
{
	int		i;
	int		srfc_count;

	i = 0;
	srfc_count = util_count_frames(eng, str);
	if (srfc_count)
	{
		res->frames_num = srfc_count;
		res->frames_delay = DEFAULT_SPRITE_DELAY;
		res->a_state = ANIMATE;
		if ((res->surface = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *)
		* srfc_count)) == NULL)
			util_malloc_error("surface");
		srfc_count = 0;
		while (srfc_count < res->frames_num)
		{
			util_create_animated_sprite2(eng, str, res, &srfc_count);
		}
		return (1);
	}
	return (0);
}
