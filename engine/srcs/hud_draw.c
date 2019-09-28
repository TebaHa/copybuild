/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:59:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/28 12:35:34 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

void		engine_draw_hud(t_engine *eng, t_player *plr, SDL_Surface *surf)
{
	int		i;
	int		x;
	int		y;
	int		tx;
	int		ty;
	int		*pix;
	int		red;
	int		green;
	int		blue;
	int		alpha;
	t_image	*img;

	i = 0;
	bresenham_line(&(t_point_3d){0, (WIDTH / 2) - 10, (HEIGHT / 2), 0}, &(t_point_3d){0, (WIDTH / 2) + 10, (HEIGHT / 2), 0}, surf, get_rgb(255, 255, 255, 255));
	bresenham_line(&(t_point_3d){0, (WIDTH / 2), (HEIGHT / 2) - 10, 0}, &(t_point_3d){0, (WIDTH / 2), (HEIGHT / 2) + 10, 0}, surf, get_rgb(255, 255, 255, 255));
	pix = (int *)surf->pixels;
	while (i < eng->stats.sprites_count)
	{
		if (plr->plr_state == P_FIRE)
		{
			if ((plr->anim % 6) == 0 || (plr->anim % 6) == 1)
			{
				if (ft_strcmp(eng->sprites_buffer[i]->filename, "rifle_fire_1.png") == 0)
				{
					img = &eng->sprites_buffer[i]->texture;
					break;
				}
			}
			else if ((plr->anim % 6) == 2 || (plr->anim % 6) == 3)
			{
				if (ft_strcmp(eng->sprites_buffer[i]->filename, "rifle_fire.png") == 0)
				{
					img = &eng->sprites_buffer[i]->texture;
					break;
				}
			}
			else if ((plr->anim % 6) == 4 || (plr->anim % 6) == 5)
			{
				if (ft_strcmp(eng->sprites_buffer[i]->filename, "rifle_fire_2.png") == 0)
				{
					img = &eng->sprites_buffer[i]->texture;
					break;
				}
			}
		}
		if (plr->plr_state == P_IDLE)
		{
			if ((plr->anim % 60) >= 0 && (plr->anim % 60) <= 19 && ft_strcmp(eng->sprites_buffer[i]->filename, "rifle_idle.png") == 0)
			{
				img = &eng->sprites_buffer[i]->texture;
				break;
			}
			else if ((plr->anim % 60) >= 20 && (plr->anim % 60) <= 39 && ft_strcmp(eng->sprites_buffer[i]->filename, "rifle_idle_1.png") == 0)
			{
				img = &eng->sprites_buffer[i]->texture;
				break;
			}
			else if ((plr->anim % 60) >= 40 && (plr->anim % 60) <= 59 && ft_strcmp(eng->sprites_buffer[i]->filename, "rifle_idle_2.png") == 0)
			{
				img = &eng->sprites_buffer[i]->texture;
				break;
			}
		}
		if (plr->plr_state == P_RELOAD && ft_strcmp(eng->sprites_buffer[i]->filename, "rifle_no_ammo.png") == 0)
		{
			img = &eng->sprites_buffer[i]->texture;
			break;
		}
		i++;
	}
	x = 0;
	tx = (WIDTH - img->width) / 2;
	while (x < img->width)
	{
		y = 0;
		ty = HEIGHT - img->height;
		while (y < img->height)
		{
			if (img->data[(y * img->channels * img->width + x * img->channels) + 3] == 255)
			{
				red = img->data[(y * img->channels * img->width + x * img->channels)];
				green = img->data[(y * img->channels * img->width + x * img->channels) + 1];
				blue = img->data[(y * img->channels * img->width + x * img->channels) + 2];
				pix[ty * WIDTH + tx] = get_rgb(red, green, blue, 255);
			}
			y++;
			ty++;
		}
		tx++;
		x++;
	}
}
