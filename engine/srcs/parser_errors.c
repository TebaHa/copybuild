/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:41:27 by fsmith            #+#    #+#             */
/*   Updated: 2019/08/07 21:41:25 by fsmith           ###   ########.fr       */
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

void	util_parsing_error_litle_data(char *problem, char *problem_from,
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

void	util_parsing_error_count_handler(char *problem, char *problem_from,
		char **str, int problems_number)
{
	if (!str[ft_atoi(str[problems_number]) + problems_number])
		util_parsing_error_litle_data(problem, problem_from, str);
	int i = 0;
	while (str[i])
	{
		ft_putnbr(i);
		ft_putstr(": ");
		ft_putendl(str[i]);
		i++;
	}
	if (str[ft_atoi(str[problems_number]) + problems_number + 1])
	{
//		ft_putnbr(ft_atoi(str[problems_number]) + problems_number + 1);
//		ft_putchar('\n');
//		char *s = str[ft_atoi(str[problems_number]) + problems_number + 1];
//		ft_putstr(str[ft_atoi(str[problems_number]) + problems_number + 1]);

		util_parsing_error_extra_data(problem, problem_from, str);
	}
}
