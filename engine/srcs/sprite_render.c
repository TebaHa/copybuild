/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 03:13:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/10 05:04:48 by zytrams          ###   ########.fr       */
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
	int		i;
	int		j;

	i = 0;
	printf("%d\n", sect->sprobjects_count);
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
		//translate sprite position to relative to camera
		double spriteX = sect->sprobjects_array[sect->order[i]].position.x - plr->position.x;
		double spriteY = sect->sprobjects_array[sect->order[i]].position.y - plr->position.y;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]
		double invDet = 1.0 / (0.0 * -1.0 - 0.0 * 0.66); //required for correct matrix multiplication

		double transformX = invDet * (0.0 * spriteX - -1.0 * spriteY);
		double transformY = invDet * (-0.66 * spriteX + 0.0 * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(HEIGHT / (transformY))); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if(drawStartY < ytop[sect_id.sx1])
			drawStartY = ytop[drawStartY];
		int drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if(drawEndY >= ybottom[sect_id.sx1])
			drawEndY = ybottom[drawEndY];
		//calculate width of the sprite
		int spriteWidth = abs( (int)(HEIGHT / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < sect_id.sx1)
			drawStartX = sect_id.sx1;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= sect_id.sx2)
			drawEndX = sect_id.sx2 - 1;

		//loop through every vertical stripe of the sprite on screen
		int stripe = drawStartX;
		while (stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * (sect->sprobjects_array[sect->order[i]].type)->anmtn[0]->surface[0]->w / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < sect_id.sx2)
			{
				j = drawStartY;
				while (j < drawEndY) //for every pixel of the current stripe
				{
					int d = (j) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * (sect->sprobjects_array[sect->order[i]].type)->anmtn[0]->surface[0]->h) / spriteHeight) / 256;
					Uint32 color = ((int *)(sect->sprobjects_array[sect->order[i]].type)->anmtn[0]->surface[0]->pixels)[sect->sprobjects_array[sect->order[i]].type->anmtn[0]->surface[0]->w * texY + texX]; //get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						((int *)surf->pixels)[j * WIDTH + stripe] = color;
					j++;
				}
			}
			stripe++;
		}
		i++;
	}
}