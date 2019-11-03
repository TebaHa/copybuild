/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:41:27 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 14:02:24 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	util_parsing_error_cant_find(char *problem, int id_problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Can't find ");
	ft_putstr(problem);
	ft_putstr(" ");
	ft_putnbr(id_problem);
	ft_putstr("!\n");
	close_game(PARSING_ERROR);
}

void	util_parsing_error_no_texture(t_image **dst, t_engine *eng,
		char *name)
{
	ft_putendl("Parsing error:");
	ft_putstr("Cant find texture: ");
	ft_putstr(name);
	ft_putstr("!\n");
	close_game(PARSING_ERROR);
}

void	util_parsing_error_no_sprite(SDL_Surface **dst, t_engine *eng,
		char *name)
{
	util_parsing_error_no_cap("sprite", eng);
	ft_putendl("Parsing error:");
	ft_putstr("Cant find sprite: ");
	ft_putstr(name);
	ft_putstr("!\n");
	close_game(PARSING_ERROR);
	util_find_sprite_by_name(dst, eng, PARSING_ERROR_SPRITE);
	if (!ft_strcmp(name, PARSING_ERROR_SPRITE))
		close_game(PARSING_ERROR);
}

void	util_parsing_error_no_cap(char *problem, t_engine *eng)
{
	if (eng->stats.cycle_detector > 1)
	{
		ft_putstr("Really cant find ");
		ft_putstr(problem);
		ft_putendl("s! Exit.");
		close_game(CYCLE_READING_ERROR);
	}
	eng->stats.cycle_detector++;
}

void	util_parsing_value_out_of_limits(int value)
{
	ft_putendl("Parsing error:");
	ft_putnbr(value);
	ft_putendl(" out of limits!");
	close_game(PARSING_ERROR);
}
