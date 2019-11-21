/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 22:49:32 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/21 22:54:30 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_replace_text(t_engine *eng, char *str)
{
	if (eng->str_info != NULL)
		free(eng->str_info);
	eng->str_info = ft_strdup(str);
	eng->text_time = TEXT_TIME;
}

void	engine_check_text(t_engine *eng)
{
	if (eng->text_time == 0)
	{
		free(eng->str_info);
		eng->str_info = NULL;
	}
	eng->text_time--;
}
