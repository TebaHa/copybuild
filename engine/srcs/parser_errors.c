/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:41:27 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/10 21:37:56 by fsmith           ###   ########.fr       */
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

void	util_parsing_error_no_texture(t_image **dst, t_engine *eng,
		char *name)
{
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
	ft_putendl("Parsing error:");
	ft_putstr("Cant find sprite: ");
	ft_putstr(name);
	ft_putstr("!\n");
	util_find_sprite_by_name(dst, eng, PARSING_ERROR_SPRITE);
	exit(PARSING_ERROR);
}

void	util_parsing_error_count_handler(char *problem, char *problem_from,
		char **str, int problems_number)
{
	if (!str[ft_atoi(str[problems_number]) + problems_number])
	{
		util_parsing_error_little_data(problem, problem_from, str);
	}
	if (str[ft_atoi(str[problems_number]) + problems_number + 1])
		util_parsing_error_extra_data(problem, problem_from, str);
}
