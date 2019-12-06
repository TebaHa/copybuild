/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharrag- <eharrag-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 11:51:43 by djast             #+#    #+#             */
/*   Updated: 2019/11/29 14:06:22 by eharrag-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

char	*cut_the_end(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] == '.')
			text[i] = '\0';
		i++;
	}
	return (text);
}

void	delete_one_symbol(t_sdl *sdl)
{
	if (sdl->map_name->text_size > 0)
	{
		sdl->map_name->text_size--;
		sdl->map_name->text[sdl->map_name->text_size] = '\0';
	}
}

void	write_to_file(int fd, char *data, int numdata)
{
	data = ft_itoa(numdata);
	write(fd, data, ft_strlen(data));
	free(data);
}
