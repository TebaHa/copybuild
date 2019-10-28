/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:52:15 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/14 19:34:21 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		parser_filename(t_engine *eng, int argc, char **argv)
{
	if (argc == 1)
		eng->map_name = ft_strdup(GAME_PATH);
	else if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "1"))
			eng->map_name = "game/resources/levels/1.lvl";
		else if (!ft_strcmp(argv[1], "2"))
			eng->map_name = "game/resources/levels/2.lvl";
		else
			eng->map_name = argv[1];
	}
	else
	{
		ft_putendl("Parsing error:");
		ft_putendl("More than one map!");
		close_game(READING_ERROR);
	}
}
