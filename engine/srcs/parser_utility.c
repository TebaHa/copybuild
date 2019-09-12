/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:12:50 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/12 21:25:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		util_create_world(t_world **world, char **str)
{
	*world = (t_world *)ft_memalloc(sizeof(t_world));
	util_int10_data_filler(&(*world)->id, str[1]);
	util_int10_data_filler(&(*world)->sectors_count, str[2]);
	util_parsing_error_count_handler("sector", "world", str, 2);
	(*world)->renderqueue = (t_item *)ft_memalloc(sizeof(t_item)
		* (*world)->sectors_count);
	(*world)->sectors_array = (t_sector *)ft_memalloc(sizeof(t_sector)
		* (*world)->sectors_count);
	(*world)->world_box = (t_sector *)ft_memalloc(sizeof(t_sector));
	(*world)->renderqueue = (t_item *)ft_memalloc(sizeof(t_item) * MAXSECTORS);
	engine_clear_renderstack((*world)->renderqueue);
}

void		util_create_point_3d(t_engine *eng, t_point_3d *point, char **str)
{
	if (!str[4])
		util_parsing_error_little_data("coordinate", "vertex", str);
	if (str[5])
		util_parsing_error_extra_data("coordinate", "vertex", str);
	util_int10_data_filler(&point->id, str[1]);
	util_float10_data_filler(&point->x, str[2]);
	util_float10_data_filler(&point->y, str[3]);
	util_float10_data_filler(&point->z, str[4]);
	eng->stats.vertexes_count++;
}

void		util_create_sprite(t_engine *eng, t_sprite *sprite, char **str)
{
	util_int10_data_filler(&sprite->id, str[1]);
	util_int10_data_filler(&sprite->frames_num, str[2]);
	util_int10_data_filler(&sprite->frames_delay, str[3]);
	sprite->a_state = STATIC;
	if (sprite->frames_num > 1)
		sprite->frames_type = 1;
	else
		sprite->frames_type = 0;
	util_find_sprite_by_name(sprite->surface, eng, str[4]);
	/* Добавить обработку лишней и недостаточной инфы */
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
	util_parsing_error_count_handler("vertex", "polygone", str, 5);
	polygone->vertices_array = (t_point_3d *)ft_memalloc(sizeof(t_point_3d)
		* polygone->vertices_count);
	str_count = 6;
	vert_count = 0;
	while (str_count < 6 + polygone->vertices_count)
		polygone->vertices_array[vert_count++] =
		util_get_vertex_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.vertexes_count, vertex_array);
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
	util_parsing_error_count_handler("polygone", "object", str, 7);
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

void		util_create_sector(t_engine *eng, t_sector *sector,
			t_object *objects_array, t_sprobject *sprobjects_array, char **str)
{
	int			obj_count;
	int			sprobj_count;
	int			str_count;

	util_int10_data_filler(&sector->id, str[1]);
	util_int10_data_filler(&sector->floor, str[2]);
	util_int10_data_filler(&sector->ceil, str[3]);
	util_find_texture_by_name(&sector->floor_texture, eng, str[4]);
	util_find_texture_by_name(&sector->ceil_texture, eng, str[5]);
	util_int10_data_filler(&sector->objects_count, str[6]);
	util_int10_data_filler(&sector->sprobjects_count, str[7]);
	if (!str[7 + sector->objects_count + sector->sprobjects_count])
		util_parsing_error_little_data("objects", "sector", str);
	if (str[8 + sector->objects_count + sector->sprobjects_count])
		util_parsing_error_extra_data("objects", "sector", str);
	sector->objects_array = (t_object *)ft_memalloc(sizeof(t_object)
		* sector->objects_count);
	sector->sprobjects_array = (t_sprobject *)ft_memalloc(sizeof(t_sprobject)
		* sector->sprobjects_count);
	str_count = 8;
	obj_count = 0;
	while (str_count < 8 + sector->objects_count)
		sector->objects_array[obj_count++] =
		util_get_object_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.objects_count, objects_array, sector->id);
	sprobj_count = 0;
	while (str_count < 8 + sector->objects_count + sector->sprobjects_count)
		sector->sprobjects_array[sprobj_count++] =
		util_get_sprobject_from_buff_by_id(ft_atoi(str[str_count++]),
		eng->stats.sprobjects_count, sprobjects_array, sector->id);
//	util_parsing_error_count_handler("object", "sector", str, 8 + sector->objects_count + sector->sprobjects_count);
	eng->stats.sectors_count++;
}

SDL_Surface	*util_transform_texture_to_sprite(t_image *texture)
{
	/* Функция перевода текстуры в спрайт не готова сосвсем */
	SDL_Surface	*sprite;
	int 		x;
	int 		y;
	int 		offset;
	int 		*pix;

	if (texture == NULL)
		return (NULL);
	sprite = SDL_CreateRGBSurface(0, texture->width, texture->height, 32, (Uint32)0xff000000,
								  (Uint32)0x00ff0000, (Uint32)0x0000ff00, (Uint32)0x000000ff);
	pix = sprite->pixels;
	x = 0;
	while (x < sprite->w)
	{
		y = 0;
		while (y < sprite->h)
		{
			offset = y * sprite->w + x;
			pix[offset] = get_rgb(texture->data[offset * texture->channels],
								  texture->data[offset * texture->channels + 1],
								  texture->data[offset * texture->channels + 2],
								  texture->data[offset * texture->channels +
												3]);
			y++;
		}
		x++;
	}
	return(sprite);
}

void		util_create_sprobject(t_engine *eng, t_sprobject *sprobject,
			t_sprite *sprite_array, t_point_3d *vertex_array, char **str)
{
	int			pol_count;
	int			str_count;

	if (!str[8])
		util_parsing_error_little_data("sprites", "sprite object", str);
	if (str[9])
		util_parsing_error_extra_data("sprites", "sprite object", str);
	util_int10_data_filler(&sprobject->id, str[1]);
	util_int10_data_filler(&sprobject->angle, str[2]);
	util_int10_data_filler(&sprobject->class, str[3]);
	sprobject->state = IDLE;
	sprobject->position = util_get_vertex_from_buff_by_id(ft_atoi(str[4]),
		eng->stats.vertexes_count, vertex_array);
	sprobject->idle = util_get_sprite_from_buff_by_id(ft_atoi(str[5]),
		eng->stats.sprites_count, sprite_array);
	sprobject->death = util_get_sprite_from_buff_by_id(ft_atoi(str[6]),
		eng->stats.sprites_count, sprite_array);
	sprobject->attack = util_get_sprite_from_buff_by_id(ft_atoi(str[7]),
		eng->stats.sprites_count, sprite_array);
	sprobject->hurt = util_get_sprite_from_buff_by_id(ft_atoi(str[8]),
		eng->stats.sprites_count, sprite_array);
//	util_parsing_error_count_handler("sprites", "sprite object", str, 8);
	eng->stats.objects_count++;
}
