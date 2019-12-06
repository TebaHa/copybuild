/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:34:40 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 21:03:41 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

SDL_Rect	*create_rect(int x, int y, int w, int h)
{
	SDL_Rect *r;

	r = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	r->x = x;
	r->y = y;
	r->w = w;
	r->h = h;
	return (r);
}

void		choose_sprite_color(t_sdl *sdl, t_ed_sprite *sprites)
{
	if (sprites->type == MEDKIT_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 255, 051, 051, 0);
	else if (sprites->type == ARMOR_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 051, 102, 153, 0);
	else if (sprites->type == POWER_UP_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 051, 102, 051, 0);
	else if (sprites->type == RIFLE_AMMO_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 204, 153, 000, 0);
	else if (sprites->type == PLASMA_GUN_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 000, 0);
	else if (sprites->type == PLASMA_AMMO_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 204, 255, 000, 0);
	else if (sprites->type == BARREL_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 102, 051, 000, 0);
	else if (sprites->type == AFRIT_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 204, 000, 000, 0);
	else if (sprites->type == CACODEMON_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 150, 000, 100, 0);
	else if (sprites->type == IMP_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 200, 100, 100, 0);
	else if (sprites->type == JETPACK_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 000, 000, 255, 0);
}

t_ed_sector	*get_last_sector(t_ed_sector *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

t_ed_sprite	*find_last_sprite(t_ed_sprite *sprites)
{
	if (sprites == NULL)
		return (NULL);
	while (sprites->next != NULL)
		sprites = sprites->next;
	return (sprites);
}

SDL_Color	*create_sdl_color(int r, int g, int b, int a)
{
	SDL_Color *color;

	color = (SDL_Color *)malloc(sizeof(SDL_Color));
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
	return (color);
}
