/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:44:08 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/08 21:01:36 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		eng_create_weapons(t_engine *eng)
{
	eng_create_rifle(eng);
	eng_create_plasma(eng);
}

void 		eng_create_rifle(t_engine *eng)
{
	t_weapon	*rifle;

	rifle = (t_weapon *)ft_memalloc(sizeof(t_weapon));
	rifle->id = RIFLE;
	rifle->name = ft_strdup("Rifle");
	rifle->ammo = 30;
	rifle->max_ammo = 30;
	rifle->containers = 0;
	rifle->state = W_IDLE;
	rifle->frame = 0;
	rifle->bullet_hole = util_create_sprite_by_name(eng, "bullet_hole");
	rifle->anmtn[W_IDLE] = util_create_sprite_by_name(eng, "rifle_idle");
	rifle->anmtn[W_IDLE]->a_state = CYCLE;
//	rifle->anmtn[W_RUN] = util_create_sprite_by_name(eng, "rifle_run");
	rifle->anmtn[W_RUN] = rifle->anmtn[W_IDLE];
	rifle->anmtn[W_FIRE] = util_create_sprite_by_name(eng, "rifle_fire");
	rifle->anmtn[W_NO_AMMO] = util_create_sprite_by_name(eng, "rifle_no_ammo");
//	rifle->anmtn[W_RELOAD] = util_create_sprite_by_name(eng, "rifle_reload");
	rifle->anmtn[W_RELOAD] = rifle->anmtn[W_IDLE];
//	rifle->anmtn[W_HURT] = util_create_sprite_by_name(eng, "rifle_hurt");
	rifle->anmtn[W_HURT] = rifle->anmtn[W_IDLE];
	rifle->shot_sound = sound_init("rifle_shot_single");
	eng->weapon[RIFLE] = rifle;
	eng->weapon[RIFLE]->next = eng->weapon[PLASMA];
	eng->weapon[RIFLE]->prev = eng->weapon[PLASMA];
}

void 		eng_create_plasma(t_engine *eng)
{
	t_weapon	*plasma;

	plasma = (t_weapon *)ft_memalloc(sizeof(t_weapon));
	plasma->id = PLASMA;
	plasma->name = ft_strdup("Plazma gun");
	plasma->ammo = 5;
	plasma->max_ammo = 5;
	plasma->containers = 0;
	plasma->state = W_IDLE;
	plasma->bullet_hole = util_create_sprite_by_name(eng, "plasma_hole");
	plasma->anmtn[W_IDLE] = util_create_sprite_by_name(eng, "plasma_idle");
//	plasma->anmtn[W_RUN] = util_create_sprite_by_name(eng, "plasma_run");
	plasma->anmtn[W_RUN] = plasma->anmtn[W_IDLE];
	plasma->anmtn[W_FIRE] = util_create_sprite_by_name(eng, "plasma_fire");
	plasma->anmtn[W_NO_AMMO] = util_create_sprite_by_name(eng, "plasma_no_ammo");
//	plasma->anmtn[W_RELOAD] = util_create_sprite_by_name(eng, "plasma_reload");
	plasma->anmtn[W_RELOAD] = plasma->anmtn[W_IDLE];
//	plasma->anmtn[W_HURT] = util_create_sprite_by_name(eng, "plasma_hurt");
	plasma->anmtn[W_HURT] = plasma->anmtn[W_IDLE];
	plasma->shot_sound = sound_init("plasma_shot_single");
	eng->weapon[PLASMA] = plasma;
	eng->weapon[PLASMA]->next = eng->weapon[RIFLE];
	eng->weapon[PLASMA]->prev = eng->weapon[RIFLE];
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
	/* Подтекаем прямо на строчку ниже!!! */
//		free(name);
	if (srfc_count)
	{
		res->frames_num = srfc_count;
		res->frames_delay = DEFAULT_SPRITE_DELAY;
		res->a_state = ANIMATE;
		/* Вероятное место утечки. Малочу под массив, но потом переопределяю */
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
					/* Вероятное место утечки. Малочу под массив, но потом переопределяю */
					res->surface[srfc_count] =
							util_transform_texture_to_sprite(
									&eng->sprites_buffer[i]->texture);
					srfc_count++;
					free(name);
					break;
				}
				i++;
			}
//			free(name);
		}
//		free(name);
		return (1);
	}
	return (0);
}

t_sprite	*util_create_sprite_by_name(t_engine *eng, char *str)
{
	t_sprite *res;
//	char *name;
//	int i;
//	int srfc_count;

	res = (t_sprite *) ft_memalloc(sizeof(t_sprite));
	res->frames_delay = DEFAULT_SPRITE_DELAY;
	/* Поиск статичного спрайта*/
//	i = 0;
//	name = util_add_png_to_name(str);
//	while (i < eng->stats.sprites_count)
//	{
//		if (!ft_strcmp(name, eng->sprites_buffer[i]->filename))
//		{
//			res->frames_num = 1;
//			res->a_state = STATIC;
//			res->surface = util_transform_texture_to_sprite(
//				&eng->sprites_buffer[i]->texture);
//			res->name = util_add_png_to_name(str);
//			break;
//		}
//		i++;
//	}
//	free (name);
//	if (i < eng->stats.sprites_count)
//		return (res);
	if (util_create_static_sprite(eng, str, res))
		return (res);
	else if (util_create_animated_sprite(eng, str, res))
		return (res);
	/* Поиск динамичного спрайта*/
//	else
//	{
//		i = 0;
//		srfc_count = 0;
//		/* Подсчет количества фреймов */
//		while (i != eng->stats.sprites_count)
//		{
//			name = util_add_png_num_to_name(str, srfc_count + 1);
//			while (i < eng->stats.sprites_count)
//			{
//				if (!ft_strcmp(name, eng->sprites_buffer[i]->filename))
//				{
//					srfc_count++;
//					free(name);
//					i = 0;
//					break;
//				}
//				i++;
//			}
//		}
//		/* Подтекаем прямо на строчку ниже!!! */
////		free(name);
//		if (srfc_count)
//		{
//			res->frames_num = srfc_count;
//			res->frames_delay = DEFAULT_SPRITE_DELAY;
//			res->a_state = ANIMATE;
//			/* Вероятное место утечки. Малочу под массив, но потом переопределяю */
//			res->surface = (SDL_Surface *) ft_memalloc(sizeof(SDL_Surface)
//				* srfc_count);
//			srfc_count = 0;
//			while (srfc_count < res->frames_num)
//			{
//				name = util_add_png_num_to_name(str, srfc_count + 1);
//				i = 0;
//				while (i < eng->stats.sprites_count)
//				{
//					if (!ft_strcmp(name, eng->sprites_buffer[i]->filename))
//					{
//						/* Вероятное место утечки. Малочу под массив, но потом переопределяю */
//						res->surface[srfc_count] =
//							*util_transform_texture_to_sprite(
//							&eng->sprites_buffer[i]->texture);
//						srfc_count++;
//						break;
//					}
//					i++;
//				}
//				free(name);
//			}
//			res->name = util_add_png_to_name(str);
//			return (res);
//		}
//	}
	res->frames_num = 1;
	res->a_state = STATIC;
	util_parsing_error_no_sprite(*res->surface, eng, str);
	res->name = util_add_png_to_name(PARSING_ERROR_SPRITE);
	return (res);
}
