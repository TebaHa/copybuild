/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:12:50 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/18 20:02:08 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		util_release_read_buffers(t_buff *buff)
{
	free(buff->vertexes);
	free(buff->polies);
	free(buff->objects);
	free(buff->sprobjects);
	free(buff->sprites);
	free(buff->sectors);
	util_release_char_matrix(buff->str);
}

void		util_release_char_matrix(char **mtrx)
{
	int		i;

	i = 0;
	while (mtrx[i] != NULL)
	{
		free(mtrx[i]);
		i++;
	}
	free(mtrx);
}

char		*util_add_png_to_name(char *old_name)
{
	char	*new_name;

	new_name = ft_strjoin(old_name, ".png");
	return (new_name);
}

char		*util_add_png_num_to_name(char *old_name, int num)
{
	char	*new_name;
	char	*new_num;

	new_num = ft_itoa(num);
	new_name = ft_strnew(ft_strlen(old_name) + ft_strlen("_.png")
		+ ft_strlen(new_num));
	new_name = ft_strcpy(new_name, old_name);
	new_name = ft_strcat(new_name, "_");
	new_name = ft_strcat(new_name, new_num);
	new_name = ft_strcat(new_name, ".png");
	free(new_num);
	return (new_name);
}

void		infinite_loop(void)
{
	while (1)
		;
}
