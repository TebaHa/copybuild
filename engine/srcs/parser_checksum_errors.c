/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:36:00 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 22:45:25 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

void		crc_message_ok(char *filename, char *result)
{
	ft_putstr(filename);
	ft_putstr(" OK: ");
	ft_putendl(result);
}

void		crc_message_error(char *filename, char *problem)
{
	ft_putstr(filename);
	ft_putstr(" KO: ");
	ft_putendl(problem);
}
