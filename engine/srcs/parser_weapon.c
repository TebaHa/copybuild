/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:44:08 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/22 19:04:59 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void 		eng_create_rifle(t_engine *eng)
{
	eng->weapon->id = 0;
	eng->weapon->name = ft_strdup("Rifle");
	eng->weapon->ammo = 30;
	eng->weapon->max_ammo = 30;
	eng->weapon->containers = 0;
	eng->weapon->state = W_IDLE;
	eng->weapon->anmtn = (t_hud_sprite *)ft_memalloc(sizeof(t_hud_sprite) *
		W_STATES_NUM);
	eng->weapon->bullet_hole = util_create_sprite_by_name(eng, "bullet_hole");

//	util_create_sprite(eng, eng->weapon->bullet_hole, "bullet_hole");
//	eng->weapon->anmtn[W_IDLE] = util_create_sprite_by_name(eng, "rifle_idle");
//	eng->weapon->anmtn[W_RUN] = util_get_hud_sprite_from_buff("rifle_run",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->anmtn[W_FIRE] = util_get_hud_sprite_from_buff("rifle_fire",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->anmtn[W_NO_AMMO] = util_get_hud_sprite_from_buff("rifle_no_ammo",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->anmtn[W_RELOAD] = util_get_hud_sprite_from_buff("rifle_reload",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->anmtn[W_HURT] = util_get_hud_sprite_from_buff("rifle_hurt",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->bullet_hole = util_get_sprite_from_buff_by_name("bullet_hole",
//		*eng->sprites_buffer, eng->stats.sprites_count);
}

void 		eng_create_plazma(t_engine *eng)
{
//	eng->weapon->id = 0;
//	eng->weapon->name = ft_strdup("Plazma gun");
//	eng->weapon->ammo = 30;
//	eng->weapon->max_ammo = 30;
//	eng->weapon->containers = 0;
//	eng->weapon->state = W_IDLE;
//	eng->weapon->anmtn[W_IDLE] = util_get_hud_sprite_from_buff("rifle_idle",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->anmtn[W_RUN] = util_get_hud_sprite_from_buff("rifle_run",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->anmtn[W_FIRE] = util_get_hud_sprite_from_buff("rifle_fire",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->anmtn[W_NO_AMMO] = util_get_hud_sprite_from_buff("rifle_no_ammo",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->anmtn[W_RELOAD] = util_get_hud_sprite_from_buff("rifle_reload",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->anmtn[W_HURT] = util_get_hud_sprite_from_buff("rifle_hurt",
//		*eng->sprites_buffer, eng->stats.sprites_count);
//	eng->weapon->bullet_hole = util_get_sprite_from_buff_by_name("bullet_hole",
//		*eng->sprites_buffer, eng->stats.sprites_count);
}

char		*util_add_png_to_name(char *old_name)
{
	char	*new_name;

	new_name = ft_strnew(ft_strlen(old_name) + ft_strlen(".png"));
	new_name = ft_strcpy(new_name, old_name);
	new_name = ft_strcat(new_name, ".png");
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

t_sprite	*util_create_sprite_by_name(t_engine *eng, char *str)
{
	t_sprite *res;
	char *name;
	int i;
	int srfc_count;

	res = (t_sprite *) ft_memalloc(sizeof(t_sprite));
	res->frames_delay = DEFAULT_SPRITE_DELAY;
	/* Поиск статичного спрайта*/
	i = 0;
	name = util_add_png_to_name(str);
	while (i < eng->stats.sprites_count)
	{
		if (!ft_strcmp(name, eng->sprites_buffer[i]->filename))
		{
			res->frames_num = 1;
			res->a_state = STATIC;
			res->surface = util_transform_texture_to_sprite(
				&eng->sprites_buffer[i]->texture);
			res->name = util_add_png_to_name(str);
			break;
		}
		i++;
	}
	free (name);
	if (i < eng->stats.sprites_count)
		return (res);
	/* Поиск динамичного спрайта*/
	else
	{
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
		{
			res->frames_num = srfc_count;
			res->frames_delay = DEFAULT_SPRITE_DELAY;
			res->a_state = ANIMATE;
			res->surface = (SDL_Surface *) ft_memalloc(sizeof(SDL_Surface)
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
						res->surface[srfc_count] = *util_transform_texture_to_sprite(
							&eng->sprites_buffer[i]->texture);
						srfc_count++;
						i = 0;
						break;
					}
					i++;
				}
				free(name);
			}
			res->name = util_add_png_to_name(str);
			return (res);
		}
	}
//	res->frames_num = 1;
//	res->a_state = STATIC;
//	util_parsing_error_no_sprite(res->surface, eng, str);
//	res->name = util_add_png_to_name(PARSING_ERROR_SPRITE);
	return (res);
}
