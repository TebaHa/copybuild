/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:41:27 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 14:02:24 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	util_parsing_value_out_of_limits(char *str)
{
	ft_putendl("Parsing error: ");
	ft_putstr(str);
	ft_putendl(" out of limits!");
	close_game(PARSING_ERROR);
}

void	util_parsing_error_double_portal(int sect_1, int sect_2)
{
	ft_putendl("Parsing error:");
	ft_putstr("Double portal from sector ");
	ft_putnbr(sect_1);
	ft_putstr(" to sector ");
	ft_putnbr(sect_2);
	ft_putstr("!\n");
	close_game(PARSING_ERROR);
}

void	util_malloc_error(char *str)
{
	ft_putendl("Malloc error: ");
	ft_putstr(str);
	ft_putendl(" not allocated!");
	close_game(MALLOC_ERROR);
}
