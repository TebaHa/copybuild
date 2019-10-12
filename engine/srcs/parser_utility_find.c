/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utility_find.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:56:36 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/28 12:35:34 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		util_find_texture_by_name(t_image **dst, t_engine *eng,
			char *name)
{
	int		i;
	int		find;
	char	*name_png;

	i = 0;
	find = 0;
	name_png = ft_strnew(ft_strlen(name) + ft_strlen(".png"));
	name_png = ft_strcat(ft_strcpy(name_png, name), ".png");
	while (i < eng->stats.textures_count)
	{
		if (!ft_strcmp(name_png, eng->texture_buffer[i]->filename))
		{
			*dst = &eng->texture_buffer[i]->texture;
			find = 1;
		}
		i++;
	}
	if (i >= eng->stats.textures_count && !find)
		util_parsing_error_no_texture(dst, eng, name);
	else
		eng->stats.cycle_detector = 0;
	free(name_png);
}

void		util_find_sprite_by_name(SDL_Surface *dst, t_engine *eng,
			char *name)
{
	int		i;
	char	*name_png;

	i = 0;
	if (!name)
	{
		dst = NULL;
		return ;
	}
	name_png = util_add_png_to_name(name);
	while (i < eng->stats.sprites_count)
	{
		if (!ft_strcmp(name_png, eng->sprites_buffer[i]->filename))
		{
			dst = util_transform_texture_to_sprite(
				&eng->sprites_buffer[i]->texture);
			break;
		}
		i++;
	}
	free(name_png);
	if (i == eng->stats.sprites_count)
		util_parsing_error_no_sprite(dst, eng, name);
	else
		eng->stats.cycle_detector = 0;
}

t_sprobject		util_get_sprobject_from_buff_by_id(int id, int size,
				t_sprobject *sprobjects, int sector_id)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (sprobjects[i].id == id)
			break;
		i++;
	}
	return (sprobjects[i]);
}

t_sprite		util_get_sprite_from_buff_by_id(int id, int size,
				t_sprite *sprites, int sprobj_id)
{
	t_sprite	res;
	int			i;

	if (id < 0)
	{
		/* Дописать кусок обработки, когда просто нет отображения никакого */
		ft_putendl("Вернуть пустой спрайт");
		exit(PARSING_ERROR);
	}
	i = 0;
	while (i < size)
	{
		if (sprites[i].id == id)
			break;
		i++;
	}
	if (i == size)
		util_parsing_error_lost_handler("sprite", id, "sprobject", sprobj_id);
	return (sprites[i]);
}

t_point_3d		util_get_vertex_from_buff_by_id(int id, int size,
				t_point_3d *vertexes, int polygone_id)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (vertexes[i].id == id)
			break;
		i++;
	}
	if (i == size)
		util_parsing_error_lost_handler("vertex", id, "polygone", polygone_id);
	return (vertexes[i]);
}

t_polygone		util_get_polygone_from_buff_by_id(int id, int size,
				t_polygone *polies, int object_id)
{
	t_polygone	res;
	int			i;

	i = 0;
	while (i < size)
	{
		if (polies[i].id == id)
			break;
		i++;
	}
	if (i == size)
		util_parsing_error_lost_handler("polygone", id, "object", object_id);
	return (polies[i]);
}

t_object		util_get_object_from_buff_by_id(int id, int size,
				t_object *objects, int sector_id)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (objects[i].id == id)
			break;
		i++;
	}
	if (i == size)
		util_parsing_error_lost_handler("object", id, "sector", sector_id);
	return (objects[i]);
}
