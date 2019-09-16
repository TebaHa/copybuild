/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:41:27 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/16 21:41:20 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	util_parsing_error_lost_handler(char *problem, int id_problem,
		char *problem_from, int id_problem_from)
{
	ft_putendl("Parsing error:");
	ft_putstr("Can't find ");
	ft_putstr(problem);
	ft_putstr(" ");
	ft_putnbr(id_problem);
	ft_putstr(" from ");
	ft_putstr(problem_from);
	ft_putstr(" ");
	ft_putnbr(id_problem_from);
	ft_putstr("!\n");
	exit(PARSING_ERROR);
}

void	util_parsing_error_extra_data(char *problem, char *problem_from,
		char **str)
{
	ft_putendl("Parsing error:");
	ft_putstr("Extra ");
	ft_putstr(problem);
	ft_putstr(" in ");
	ft_putstr(problem_from);
	ft_putstr(" ");
	ft_putstr(str[1]);
	ft_putstr("!\n");
	exit(PARSING_ERROR);
}

void	util_parsing_error_little_data(char *problem, char *problem_from,
		char **str)
{
	ft_putendl("Parsing error:");
	ft_putstr("Not enough ");
	ft_putstr(problem);
	ft_putstr(" in ");
	ft_putstr(problem_from);
	ft_putstr(" ");
	ft_putstr(str[1]);
	ft_putstr("!\n");
	exit(PARSING_ERROR);
}

void	util_parsing_error_not_digit(char *problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Not only digits in this data: ");
	ft_putstr(problem);
	ft_putstr("!\n");
	exit(PARSING_ERROR);
}

void	util_parsing_error_not_hex(char *problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Not hex data: ");
	ft_putstr(problem);
	ft_putstr("!\n");
	exit(PARSING_ERROR);
}

void	util_parsing_error_cant_find(char *problem, int id_problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Can't find ");
	ft_putstr(problem);
	ft_putstr(" ");
	ft_putnbr(id_problem);
	ft_putstr("!\n");
	exit(PARSING_ERROR);
}

void	util_parsing_error_no_texture(t_image **dst, t_engine *eng,
		char *name)
{
	util_parsing_error_no_cap("texture", eng);
	ft_putendl("Parsing error:");
	ft_putstr("Cant find texture: ");
	ft_putstr(name);
	ft_putstr("!\n");
	util_find_texture_by_name(dst, eng, PARSING_ERROR_TEXTURE);
	exit(PARSING_ERROR);
}

void	util_parsing_error_no_sprite(SDL_Surface *dst, t_engine *eng,
		char *name)
{
	util_parsing_error_no_cap("sprite", eng);
	ft_putendl("Parsing error:");
	ft_putstr("Cant find sprite: ");
	ft_putstr(name);
	ft_putstr("!\n");
	util_find_sprite_by_name(dst, eng, PARSING_ERROR_SPRITE);
	exit(PARSING_ERROR);
}

void	util_parsing_error_count_handler(char *problem_from, char **str,
		int problems_number)
{
	if (!str[problems_number])
		util_parsing_error_little_data("data", problem_from, str);
	if (str[problems_number + 1])
		util_parsing_error_extra_data("data", problem_from, str);
}

void util_parsing_error_no_cap(char *problem, t_engine *eng)
{
	if (eng->stats.cycle_detector > 1)
	{
		ft_putstr("Really cant find ");
		ft_putstr(problem);
		ft_putendl("s! Exit.");
		exit(CYCLE_READING_ERROR);
	}
	eng->stats.cycle_detector++;
}
