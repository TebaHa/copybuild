/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:03:24 by zytrams           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/10/01 20:24:17 by zytrams          ###   ########.fr       */
=======
/*   Updated: 2019/09/28 12:35:34 by fsmith           ###   ########.fr       */
>>>>>>> d3683f2794205af1c7c9edaf58fda7f2b7634fcc
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
