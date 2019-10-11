/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 03:13:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/11 03:19:33 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

void		engine_render_sprites(t_engine *eng, t_player *plr, SDL_Surface *surf, int *ytop, int *ybottom)
{
	t_item		sect_id;
	t_sector	*sect;

	while (((sect_id = engine_pop_renderstack(eng->world->sprite_renderqueue)).sectorno >= 0))
	{
		sect = eng->world->sectors_array + sect_id.sectorno;
		engine_render_sprites_in_sector(sect, surf, plr,
		ytop, ybottom, sect_id);
	}
}

void		engine_render_sprites_in_sector(t_sector *sect, SDL_Surface *surf, t_player *plr, int *ytop, int *ybottom, t_item sect_id)
{
	int				i;
	int				j;
	double			planeX;
	double			planey;

	i = 0;
	while (i < sect->sprobjects_count)
	{
		sect->order[i] = i;
		sect->dist[i] = ((plr->position.x - sect->sprobjects_array[i].position.x) * (plr->position.x - sect->sprobjects_array[i].position.x)
		+ (plr->position.y - sect->sprobjects_array[i].position.y) * (plr->position.x  - sect->sprobjects_array[i].position.y));
		i++;
	}
	sprite_comb_sort(sect);
	i = 0;
	while (i < sect->sprobjects_count)
	{
		//printf("%d\n", i);
		//translate sprite position to relative to camera
		double dirX = -plr->sinangle, dirY = plr->cosangle; //initial direction vector
		double planeX = plr->cosangle, planeY = plr->sinangle; //the 2d raycaster version of camera pla
		double spriteX = sect->sprobjects_array[sect->order[i]].position.x - plr->position.x;
		double spriteY = sect->sprobjects_array[sect->order[i]].position.y - plr->position.y;
		//printf("%f %f\n", spriteX, spriteY);
		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]
		double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

		double transformX = invDet * (dirY * spriteX - dirX * spriteY);
		double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
		//printf("%d\n", spriteScreenX);
		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(HEIGHT / (transformY))); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		drawStartY = clamp(0, ytop[sect_id.sx1], drawStartY);
		int drawEndY = spriteHeight / 2 + HEIGHT / 2;
		drawEndY = clamp(drawEndY, ybottom[sect_id.sx1], HEIGHT - 1);
		//calculate width of the sprite
		int spriteWidth = abs( (int)(HEIGHT / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		drawStartX = min(sect_id.sx1, drawStartX);
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		drawEndX = min(sect_id.sx2, drawEndX);
		//loop through every vertical stripe of the sprite on screen
		int stripe = drawStartX;
		//printf("%d %d\n", drawStartX, drawEndX);
		while (stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * (sect->sprobjects_array[sect->order[i]].type)->anmtn[0]->surface[0]->w / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < WIDTH)
			{
				j = drawStartY;
				while (j < drawEndY) //for every pixel of the current stripe
				{
					int d = (j) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * (sect->sprobjects_array[sect->order[i]].type)->anmtn[0]->surface[0]->h) / spriteHeight) / 256;
					Uint32 color = ((int *)(sect->sprobjects_array[sect->order[i]].type)->anmtn[0]->surface[0]->pixels)[sect->sprobjects_array[sect->order[i]].type->anmtn[0]->surface[0]->w * texY + texX]; //get current color from the texture
					if((color & 0x00FFFFFF) != 0)
						((int *)surf->pixels)[j * WIDTH + stripe] = color;
					j++;
				}
			}
			stripe++;
		}
		i++;
	}
}