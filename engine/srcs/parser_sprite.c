/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_sprite	*engine_read_sprites_from_file(t_engine *eng,
			t_buff buff)
{
	t_sprite	*sprites_buff;
	char		**splitted_line;
	int			i;

	sprites_buff = (t_sprite *)ft_memalloc(sizeof(t_sprite) *
										   eng->stats.skins_count);
	i = 0;
	eng->stats.skins_count = 0;
	while (buff.str[i] != NULL)
	{
		splitted_line = ft_strsplitwhitespaces(buff.str[i]);
		if (ft_strcmp(splitted_line[0], "sprite:") == 0)
			util_create_sprite(eng, &sprites_buff[eng->stats.skins_count],
							   splitted_line);
		util_release_char_matrix(splitted_line);
		i++;
	}
	return (sprites_buff);
}

