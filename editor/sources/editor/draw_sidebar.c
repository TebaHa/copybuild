/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sidebar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:31:52 by eharrag-          #+#    #+#             */
/*   Updated: 2019/12/06 21:04:17 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_text(t_sdl *sdl, char *text, SDL_Rect button, SDL_Color color)
{
	sdl->surface = TTF_RenderText_Solid(sdl->font, text, color);
	sdl->text = SDL_CreateTextureFromSurface(sdl->renderer,
											sdl->surface);
	SDL_FreeSurface(sdl->surface);
	SDL_RenderCopy(sdl->renderer, sdl->text, NULL, &button);
	SDL_DestroyTexture(sdl->text);
}

void	choose_color_of_button(t_sdl *sdl, int color)
{
	if (color == COLOR_PUSHED && sdl->button_pushed == PLAYER_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 50, 205, 50, 100);
	else if (color == COLOR_PUSHED && sdl->button_pushed == MEDKIT_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 255, 051, 051, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == ARMOR_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 051, 102, 153, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == POWER_UP_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 051, 102, 051, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == RIFLE_AMMO_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 204, 153, 000, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == PLASMA_GUN_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 000, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == PLASMA_AMMO_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 204, 255, 000, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == BARREL_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 102, 051, 000, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == AFRIT_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 204, 000, 000, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == CACODEMON_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 150, 000, 100, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == IMP_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 200, 100, 100, 0);
	else if (color == COLOR_PUSHED && sdl->button_pushed == JETPACK_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 000, 000, 255, 0);
}

void	draw_button(t_sdl *sdl, SDL_Rect button, char *text, int color)
{
	SDL_Color	*color_text;

	choose_color_of_button(sdl, color);
	if (color == COLOR_PUSHED && sdl->button_pushed == WALL_PUSH)
		SDL_SetRenderDrawColor(sdl->renderer, 153, 204, 255, 0);
	if (color == COLOR_UNPUSHED)
		SDL_SetRenderDrawColor(sdl->renderer, 025, 000, 051, 255);
	if (color == SAVE_BUTTON)
		SDL_SetRenderDrawColor(sdl->renderer, 050, 000, 100, 255);
	SDL_RenderFillRect(sdl->renderer, &button);
	color_text = create_sdl_color(204, 153, 255, 255);
	draw_text(sdl, text, button, *color_text);
	free(color_text);
}

void	draw_buttons_on_sidebar(t_sdl *sdl)
{
	SDL_Rect	*button;

	button = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	player_button(sdl, button);
	medkit_button(sdl, button);
	armor_button(sdl, button);
	power_up_button(sdl, button);
	rifle_ammo_button(sdl, button);
	plasma_gun_button(sdl, button);
	plasma_ammo_button(sdl, button);
	barrel_button(sdl, button);
	afrit_button(sdl, button);
	cacodemon_button(sdl, button);
	imp_button(sdl, button);
	jetpack_button(sdl, button);
	wall_button(sdl, button);
	save_button(sdl, button);
	status_text(sdl, button);
	free(button);
}

void	draw_sidebar(t_sdl *sdl)
{
	SDL_Rect	sidebar;

	sidebar.x = SIZE_WIN_X * 0.8;
	sidebar.y = 0;
	sidebar.w = SIZE_WIN_X * 0.2;
	sidebar.h = SIZE_WIN_Y;
	SDL_SetRenderDrawColor(sdl->renderer, 20, 20, 40, 0);
	SDL_RenderFillRect(sdl->renderer, &sidebar);
	draw_buttons_on_sidebar(sdl);
	input_field(sdl);
}
