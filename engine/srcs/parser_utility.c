/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:12:50 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 19:07:36 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		util_create_world(t_world **world, char **str)
{
	*world = (t_world *)ft_memalloc(sizeof(t_world));
	util_int10_data_filler(&(*world)->id, str[1]);
	util_int10_data_filler(&(*world)->sectors_count, str[2]);
	if (!(*world)->sectors_count)
		util_parsing_error_little_data("sectors", "world", str);
	util_parsing_error_count_handler("world", str, 2 + (*world)->sectors_count);
//	(*world)->renderstack = (t_item *)ft_memalloc(sizeof(t_item)
//		* (*world)->sectors_count);
	(*world)->renderstack = (t_item *)ft_memalloc(sizeof(t_item) * MAXSECTORS);
	(*world)->sectors_array = (t_sector *)ft_memalloc(sizeof(t_sector)
		* (*world)->sectors_count);
	(*world)->world_box = (t_sector *)ft_memalloc(sizeof(t_sector));
	(*world)->sprite_renderstack =
		(t_item_sprts **)ft_memalloc(sizeof(t_item_sprts *) * MAXSECTORS);
	engine_clear_renderstack((*world)->renderstack);
	engine_clear_spriterenderstack((*world)->sprite_renderstack);
}

void		util_create_point_3d(t_engine *eng, t_point_3d *point, char **str)
{
	util_parsing_error_count_handler("vertex", str, 4);
	util_int10_data_filler(&point->id, str[1]);
	util_float10_data_filler(&point->x, str[2]);
	util_float10_data_filler(&point->y, str[3]);
	util_float10_data_filler(&point->z, str[4]);
	eng->stats.vertexes_count++;
}

void		util_create_sprite(t_engine *eng, t_sprite *sprite, char **str)
{
	int 	srfc_count;
	char 	*name;

	util_parsing_error_count_handler("sprite", str, 4);
	util_int10_data_filler(&sprite->id, str[1]);
	util_int10_data_filler(&sprite->frames_num, str[2]);
	util_int10_data_filler(&sprite->frames_delay, str[3]);
	sprite->surface = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *)
		* sprite->frames_num);
	sprite->a_state = STATIC;
	if (sprite->frames_num > 1)
	{
		sprite->a_state = ANIMATE;
		srfc_count = 1;
		while (srfc_count <= sprite->frames_num)
		{
			name = ft_strcpy(ft_strnew(ft_strlen(str[4]) + 2), str[4]);
			name = ft_strcat(ft_strcat(name, "_"), ft_itoa(srfc_count));
			util_find_sprite_by_name(&sprite->surface[srfc_count], eng, name);
			free(name);
			srfc_count++;
		}
	}
	else
	{
		sprite->a_state = STATIC;
		util_find_sprite_by_name(sprite->surface, eng, str[4]);
	}
	eng->stats.skins_count++;
}

void		util_create_polygone(t_engine *eng, t_polygone *polygone,
			t_point_3d *vertex_array, char **str)
{
	int			vert_count;
	int			str_count;

	util_int10_data_filler(&polygone->id, str[1]);
	util_int10_data_filler(&polygone->type, str[2]);
	util_int16_data_filler(&polygone->color, str[3]);
	util_find_texture_by_name(&polygone->texture, eng, str[4]);
	util_int10_data_filler(&polygone->vertices_count, str[5]);
	if (!polygone->vertices_count)
		util_parsing_error_little_data("vertices", "polygone", str);
	util_parsing_error_count_handler("polygone", str, 5 + polygone->vertices_count);
	polygone->vertices_array = (t_point_3d *)ft_memalloc(sizeof(t_point_3d)
		* polygone->vertices_count);
	str_count = 6;
	vert_count = 0;
	while (str_count < 6 + polygone->vertices_count)
		polygone->vertices_array[vert_count++] =
		util_get_vertex_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.vertexes_count, vertex_array, polygone->id);
	eng->stats.polies_count++;
}

void		util_create_object(t_engine *eng, t_object *object,
			t_polygone *polygone_array, char **str)
{
	int			pol_count;
	int			str_count;

	util_int10_data_filler(&object->id, str[1]);
	util_int10_data_filler(&object->portal, str[2]);
	util_int10_data_filler(&object->passble, str[3]);
	util_int10_data_filler(&object->visible, str[4]);
	util_find_texture_by_name(&object->floor_wall_texture, eng, str[5]);
	util_find_texture_by_name(&object->ceil_wall_texture, eng, str[6]);
	util_int10_data_filler(&object->polies_count, str[7]);
	if (!object->polies_count)
		util_parsing_error_little_data("polies", "object", str);
	util_parsing_error_count_handler("object", str, 7 + object->polies_count);
	object->polies_array = (t_polygone *)ft_memalloc(sizeof(t_polygone)
		* object->polies_count);
	str_count = 8;
	pol_count = 0;
	while (str_count < 8 + object->polies_count)
		object->polies_array[pol_count++] =
		util_get_polygone_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.polies_count, polygone_array, object->id);
	eng->stats.objects_count++;
}

void		util_create_sector(t_engine *eng, t_buff buff,
			t_sector *sector, char **str)
{
	int			obj_count;
	int			str_count;

	util_int10_data_filler(&sector->id, str[1]);
	util_int10_data_filler(&sector->floor, str[2]);
	util_int10_data_filler(&sector->ceil, str[3]);
	util_find_texture_by_name(&sector->floor_texture, eng, str[4]);
	util_find_texture_by_name(&sector->ceil_texture, eng, str[5]);
	util_int10_data_filler(&sector->objects_count, str[6]);
	if (sector->objects_count < 3)
		util_parsing_error_little_data("objects", "sector", str);
	util_int10_data_filler(&sector->sprobjects_count, str[7]);
	util_parsing_error_count_handler("sector", str, 7 + sector->objects_count
		+ sector->sprobjects_count);
	sector->objects_array = (t_object *)ft_memalloc(sizeof(t_object)
		* sector->objects_count);
	str_count = 8;
	obj_count = 0;
	while (str_count < 8 + sector->objects_count)
		sector->objects_array[obj_count++] =
		util_get_object_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.objects_count, buff.objects, sector->id);
	util_create_sector_sprobjs(eng, buff, sector, str);
	sector->dist = (double *)ft_memalloc(sizeof(double) * sector->objects_count);
	sector->order = (int *)ft_memalloc(sizeof(int) * sector->objects_count);
	util_find_repeats_in_sector(sector);
	eng->stats.sectors_count++;
}

void		util_create_sector_sprobjs(t_engine *eng, t_buff buff,
			t_sector *sector, char **str)
{
	int			sprobj_count;
	int			str_count;

	sector->sprobjects_array = (t_sprobject *)ft_memalloc(sizeof(t_sprobject)
		* sector->sprobjects_count);
	str_count = 8 + sector->objects_count;
	sprobj_count = 0;
	while (str_count < 8 + sector->objects_count + sector->sprobjects_count)
		sector->sprobjects_array[sprobj_count++] =
		util_get_sprobject_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.sprobjects_count, buff.sprobjects, sector->id);
}

void		util_find_repeats_in_sector(t_sector *sector)
{
	int 	j;
	int 	i;

	i = 0;
	while (i < sector->objects_count)
	{
		j = 0;
		while (j < sector->objects_count)
		{
			if (i != j)
			{
				if (sector->objects_array[i].id == sector->objects_array[j].id)
					util_parsing_error_repetions("objects", "sector", sector->id);
				if (sector->objects_array[i].polies_array[0].id ==
					sector->objects_array[j].polies_array[0].id)
					util_parsing_error_repetions("polies", "sector", sector->id);
			}
			j++;
		}
		i++;
	}
	while (i < sector->sprobjects_count)
	{
		j = 0;
		while (j < sector->sprobjects_count)
		{
			if (sector->sprobjects_array[i].id ==
				sector->sprobjects_array[j].id && i != j)
				util_parsing_error_repetions("sprobjects", "sector", sector->id);
			j++;
		}
		i++;
	}
}

SDL_Surface	*util_CreateRGBSurface(Uint32 flags, int width, int height,
		int depth)
{
	return (SDL_CreateRGBSurface(flags, width, height, depth,
		(Uint32)0xff000000, (Uint32)0x00ff0000, (Uint32)0x0000ff00, (Uint32)0x000000ff));
}

SDL_Surface	*util_transform_texture_to_sprite(t_image *texture)
{
	SDL_Surface	*sprite;
	int 		x;
	int 		y;
	int 		offsets;
	int 		offseti;
	unsigned	*pix;

	if (texture == NULL)
		return (NULL);
	sprite = util_CreateRGBSurface(0, texture->width, texture->height, 32);
	pix = sprite->pixels;
	x = 0;
	while (x < sprite->w)
	{
		y = 0;
		while (y < sprite->h)
		{
			offsets = y * sprite->w + x;
			offseti = y * texture->width + x;
			pix[offsets] = ((unsigned *)texture->data)[offseti];
			y++;
		}
		x++;
	}
	//image_free(texture);
	return (sprite);
}

void		util_create_sprobject(t_engine *eng, t_sprobject *sprobject,
			t_sprite *sprite_array, t_point_3d *vertex_array, char **str)
{
	int			pol_count;
	int			str_count;
	util_parsing_error_count_handler("sprite object", str, 4);
	util_int10_data_filler(&sprobject->id, str[1]);
	util_int10_data_filler(&sprobject->angle, str[2]);
	if (ft_atoi(str[3]) < 0 || ft_atoi(str[3]) > ENEMY_NUM)
		util_parsing_error_cant_find("texture from sprobject", ft_atoi(str[3]));
	sprobject->enum_type = ft_atoi(str[3]);
	sprobject->type = eng->enemy[ft_atoi(str[3])];
	sprobject->position = util_get_vertex_from_buff_by_id(ft_atoi(str[4]),
		eng->stats.vertexes_count, vertex_array, sprobject->id);
	sprobject->state = E_IDLE;
	sprobject->frame = 0;
	eng->stats.sprobjects_count++;
}

void		util_release_read_buffers(t_buff *buff)
{
	free(buff->vertexes);
	free(buff->polies);
	free(buff->objects);
	free(buff->sprobjects);
	free(buff->sprites);
	util_release_char_matrix(buff->str);
}


void		infinite_loop(void)
{
	while (1)
		;
}


char		*util_add_png_to_name(char *old_name)
{
	char	*new_name;

	new_name = ft_strjoin(old_name, ".png");
	return (new_name);
}

char		*util_add_png_num_to_name(char *old_name, int num)
{
	char	*new_name;
	char 	*new_num;

	new_num = ft_itoa(num);
	new_name = ft_strnew(ft_strlen(old_name) + ft_strlen("_.png")
						 + ft_strlen(new_num));
	new_name = ft_strcpy(new_name, old_name);
	new_name = ft_strcat(new_name, "_");
	new_name = ft_strcat(new_name, new_num);
	new_name = ft_strcat(new_name, ".png");
	free(new_num);
	return (new_name);
}

int 		util_create_static_sprite(t_engine *eng, char *str, t_sprite *res)
{
	int i;

	i = 0;
	res->name = util_add_png_to_name(str);
	while (i < eng->stats.sprites_count)
	{
		if (!ft_strcmp(res->name, eng->sprites_buffer[i]->filename))
		{
			res->frames_num = 1;
			res->a_state = STATIC;
			res->surface = (SDL_Surface **) ft_memalloc(sizeof(SDL_Surface *));
			res->surface[0] = util_transform_texture_to_sprite(
					&eng->sprites_buffer[i]->texture);
			break;
		}
		i++;
	}
	if (i < eng->stats.sprites_count)
		return (1);
	return (0);
}

int 		util_create_animated_sprite(t_engine *eng, char *str, t_sprite *res)
{
	int i;
	int srfc_count;
	char *name;

	i = 0;
	srfc_count = 0;
	/* Подсчет количества фреймов */
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
				break;
			}
			i++;
		}
	}
	if (srfc_count)
		free(name);
	if (srfc_count)
	{
		res->frames_num = srfc_count;
		res->frames_delay = DEFAULT_SPRITE_DELAY;
		res->a_state = ANIMATE;
		res->surface = (SDL_Surface **) ft_memalloc(sizeof(SDL_Surface *)
													* srfc_count);
		srfc_count = 0;
		while (srfc_count < res->frames_num)
		{
			name = util_add_png_num_to_name(str, srfc_count + 1);
			i = 0;
			while (i < eng->stats.sprites_count)
			{
				if (!ft_strcmp(name, eng->sprites_buffer[i]->filename))
				{
					res->surface[srfc_count] =
							util_transform_texture_to_sprite(
									&eng->sprites_buffer[i]->texture);
					srfc_count++;
					free(name);
					break;
				}
				i++;
			}
		}
		return (1);
	}
	return (0);
}

t_sprite	*util_create_sprite_by_name(t_engine *eng, char *str)
{
	t_sprite *res;

	res = (t_sprite *) ft_memalloc(sizeof(t_sprite));
	res->surface = (SDL_Surface **) ft_memalloc(sizeof(SDL_Surface));
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
