/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:52:15 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/14 19:34:21 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

float	util_float10_data_filler(char *str, int min, int max)
{
	int		i;
	int		res;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || str[i] == '-'))
			util_parsing_error_not_digit(str);
		i++;
	}
	res = ft_atoi(str);
	if (res < min || res > max || ft_strlen(str) > 9)
		util_parsing_value_out_of_limits(str);
	return ((float)res);
}

int		util_int10_data_filler(char *str, int min, int max)
{
	int i;
	int res;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || str[i] == '-'))
			util_parsing_error_not_digit(str);
		i++;
	}
	res = ft_atoi(str);
	if (res < min || res > max || ft_strlen(str) > 9)
		util_parsing_value_out_of_limits(str);
	return (res);
}

int		util_int16_data_filler(char *str)
{
	int i;
	int res;

	if (str[0] != '0' || str[1] != 'x' || !str[2])
		util_parsing_error_not_hex(str);
	i = 2;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || (str[i] >= 'a' && str[i] <= 'f')
		|| (str[i] >= 'A' && str[i] <= 'F')))
			util_parsing_error_not_digit(str);
		i++;
	}
	res = ft_atoi_hex(str);
	if (res < 0 || res > 2147483647 || ft_strlen(str) > 9)
		util_parsing_value_out_of_limits(str);
	return (res);
}
