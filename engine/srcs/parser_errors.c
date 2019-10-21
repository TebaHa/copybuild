/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:41:27 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 14:02:24 by fsmith           ###   ########.fr       */
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
	close_game(PARSING_ERROR);
}

void	util_parsing_error_not_enough(char *problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Not enough ");
	ft_putstr(problem);
	ft_putstr(" in lvl file!\n");
	close_game(PARSING_ERROR);
}

void	util_parsing_error_lot_of(char *problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Lot of ");
	ft_putstr(problem);
	ft_putstr(" in lvl file!\n");
	close_game(PARSING_ERROR);
}

void	util_parsing_error_repeats(char *problem, char *problem_from,
		int id_problem)
{
	ft_putendl("Parsing error:");
	ft_putstr("Repeating ");
	ft_putstr(problem);
	ft_putstr(" in ");
	ft_putstr(problem_from);
	ft_putstr(" ");
	ft_putnbr(id_problem);
	ft_putstr("!\n");
	close_game(PARSING_ERROR);
}

void	util_parsing_error_little_data_check(char *problem_from, char **str,
		int problems_number)
{
	int	i;

	i = 0;
	while (i <= problems_number)
	{
		if (!str[i])
			util_parsing_error_little_data("data", problem_from, str);
		i++;
	}
}
