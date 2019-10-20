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

void	util_parsing_error_count_handler(char *problem_from, char **str,
		int problems_number)
{
	if (!str[problems_number])
		util_parsing_error_little_data("data", problem_from, str);
	if (str[problems_number + 1])
		util_parsing_error_extra_data("data", problem_from, str);
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
	close_game(PARSING_ERROR);
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
	close_game(PARSING_ERROR);
}

void	util_parsing_error_not_digit(char *problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Not only digits in this data: ");
	ft_putstr(problem);
	ft_putstr("!\n");
	close_game(PARSING_ERROR);
}

void	util_parsing_error_not_hex(char *problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Not hex data: ");
	ft_putstr(problem);
	ft_putstr("!\n");
	close_game(PARSING_ERROR);
}
