/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:03:24 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/01 23:40:15 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	error_handler(char *error_type, const char *str_error, t_engine *eng)
{
	ft_putstr(error_type);
	ft_putstr("\n");
	ft_putstr(str_error);
	ft_putstr("\n");
	engine_sdl_uninit(eng);
	exit(1);
}
