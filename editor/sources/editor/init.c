/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:27:00 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 20:55:41 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_input_field	*init_input_field(int x1, int y1, int x2, int y2)
{
	t_input_field	*field;

	field = (t_input_field *)malloc(sizeof(t_input_field));
	field->x = x1;
	field->y = y1;
	field->size_x = x2 - x1;
	field->size_y = y2 - y1;
	field->max_text_size = 20;
	field->text = ft_strnew(field->max_text_size);
	field->text_size = 0;
	return (field);
}

t_ed_sprite		*init_sprite(void)
{
	t_ed_sprite	*sprite;

	sprite = (t_ed_sprite *)malloc(sizeof(t_ed_sprite));
	sprite->type = 0;
	sprite->x = 0;
	sprite->y = 0;
	sprite->sector = 0;
	sprite->next = NULL;
	return (sprite);
}

t_ed_sector		*init_sector(void)
{
	t_ed_sector	*sector;

	sector = (t_ed_sector *)malloc(sizeof(t_ed_sector));
	ft_bzero(sector->point, 1000);
	ft_bzero(sector->walls, 1000);
	sector->size = 0;
	sector->total_num_of_obj = 0;
	sector->num_of_sector = -1;
	sector->num_of_walls = 0;
	sector->type_of_point = 0;
	sector->check = 0;
	sector->z = 300;
	sector->cmn = 0;
	sector->sh = 0;
	sector->rh = 0;
	sector->local_intersection = 0;
	sector->portal_advent = 0;
	sector->next = NULL;
	return (sector);
}

void			init_player(t_sdl *sdl)
{
	sdl->player = (t_ed_point *)malloc(sizeof(t_ed_point));
	sdl->player->x = 0;
	sdl->player->y = 0;
}

void			init_sdl(t_sdl *sdl)
{
	sdl->font = TTF_OpenFont("./editor/resources/Samson.ttf", 200);
	sdl->button_pushed = WALL_PUSH;
	sdl->sectors = init_sector();
	sdl->commands = NULL;
	sdl->command_count = 0;
	sdl->is_overlay = -1;
	sdl->sprites = NULL;
	sdl->sprite_in_sector = 0;
	sdl->id = 0;
	sdl->char_id = NULL;
	sdl->count = 0;
	sdl->num = 0;
	sdl->status_code = 1;
	sdl->is_input = 0;
	sdl->save_click = 0;
	sdl->map_name = init_input_field(INPUT_FIELD_X1, INPUT_FIELD_Y1,
									INPUT_FIELD_X2, INPUT_FIELD_Y2);
	init_player(sdl);
}
