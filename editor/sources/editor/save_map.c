/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 11:37:38 by djast             #+#    #+#             */
/*   Updated: 2019/12/06 15:15:38 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	create_file(char *map_name)
{
	int		fd;
	char	filename[120];

	ft_strcpy(filename, "resources/");
	ft_strcat(filename, map_name);
	ft_strcat(filename, ".txt");
	fd = open(filename, O_WRONLY);
	if (fd == -1)
	{
		open(filename, O_CREAT);
		fd = open(filename, O_WRONLY);
	}
	else
		return (-1);
	return (fd);
}

int			saving(t_sdl *sdl, char *map_name)
{
	int fd;
	int last_id;

	sdl->save_click = 1;
	fd = create_file(map_name);
	if (fd == -1)
		return (0);
	write_world(sdl, fd);
	write_player(sdl, fd);
	last_id = write_vertexes_wall(sdl, fd);
	write_vertexes_sprite(sdl, fd, last_id);
	write_objects(sdl, fd);
	write_sprites(sdl, fd, last_id);
	write_sectors(sdl, fd);
	close(fd);
	return (1);
}

int			save_map(t_sdl *sdl, char *map_name)
{
	find_portals(sdl);
	if (check_doubleport(sdl) == 1)
		sdl->is_doubleport = 1;
	if (check_overlays(sdl) == 1)
		sdl->is_overlay = 1;
	if (sdl->is_doubleport == 0 &&
		sdl->is_overlay == 0)
	{
		if (saving(sdl, map_name) == 0)
			return (0);
	}
	return (1);
}

void		save_click(t_sdl *sdl)
{
	if (sdl->map_name->text_size <= 0)
	{
		sdl->status_code = CODE_NO_FILENAME;
		return ;
	}
	if (!(sdl->player->x > 0 && sdl->player->y > 0))
	{
		sdl->status_code = CODE_NO_PLAYER;
		return ;
	}
	if (save_map(sdl, sdl->map_name->text) == 0)
	{
		sdl->status_code = CODE_ALREADY_EXIST;
		return ;
	}
	if (sdl->is_overlay == 1 || sdl->is_doubleport == 1)
	{
		sdl->status_code = CODE_OVERLAY_OR_DOUBLEPORT;
		return ;
	}
	bzero(sdl->map_name->text, ft_strlen(sdl->map_name->text));
	sdl->map_name->text_size = 0;
	sdl->status_code = CODE_OK;
}

int			bigscarycondition(t_sdl *sdl)
{
	SDL_GetMouseState(&sdl->mouse_position.x, &sdl->mouse_position.y);
	if (((sdl->window_event.type == SDL_KEYDOWN &&
			SDLK_KP_ENTER == sdl->window_event.key.keysym.sym) ||
			(sdl->window_event.type == SDL_KEYDOWN &&
			SDLK_RETURN == sdl->window_event.key.keysym.sym) ||
			(sdl->window_event.type == SDL_MOUSEBUTTONDOWN &&
			sdl->window_event.button.button == SDL_BUTTON_LEFT &&
			((sdl->mouse_position.x > BUTTON_SAVE_X1 &&
			sdl->mouse_position.x < BUTTON_SAVE_X2) &&
			(sdl->mouse_position.y > BUTTON_SAVE_Y1 &&
			sdl->mouse_position.y < BUTTON_SAVE_Y2)))))
		return (1);
	return (0);
}
