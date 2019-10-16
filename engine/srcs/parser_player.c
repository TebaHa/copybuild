#include <engine.h>

void		engine_check_plr_pos(t_world *world, t_player *plr)
{
	t_point_3d	temp;

	temp.x = plr->position.x - 1;
	temp.y = plr->position.y - 1;
	while (temp.x <= plr->position.x + 1)
	{
		while (temp.y <= plr->position.y + 1)
		{
			if (engine_object_get_sector(world, temp, 0) == -1)
				util_parsing_error_player_outside();
			temp.y++;
		}
		temp.x++;
	}
}
