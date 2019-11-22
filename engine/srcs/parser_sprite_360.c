/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite_360.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_sprite	**util_create_sprite_360_by_name(t_engine *eng, char *str)
{
	t_sprite **res;

	res = (t_sprite **)ft_memalloc(sizeof(t_sprite *) * EA_NUM);
	res[EA_000] = util_create_sprite_by_name_suffix(eng, str, "_000");
	res[EA_045] = util_create_sprite_by_name_suffix(eng, str, "_045");
	res[EA_090] = util_create_sprite_by_name_suffix(eng, str, "_090");
	res[EA_135] = util_create_sprite_by_name_suffix(eng, str, "_135");
	res[EA_180] = util_create_sprite_by_name_suffix(eng, str, "_180");
	res[EA_225] = util_create_sprite_by_name_suffix(eng, str, "_225");
	res[EA_270] = util_create_sprite_by_name_suffix(eng, str, "_270");
	res[EA_315] = util_create_sprite_by_name_suffix(eng, str, "_315");
	return (res);
}

t_sprite	**util_create_sprite_0_by_name(t_engine *eng, char *str)
{
	t_sprite **res;

	res = (t_sprite **)ft_memalloc(sizeof(t_sprite *) * EA_NUM);
	res[EA_000] = util_create_sprite_by_name(eng, str);
	res[EA_045] = res[EA_000];
	res[EA_090] = res[EA_000];
	res[EA_135] = res[EA_000];
	res[EA_180] = res[EA_000];
	res[EA_225] = res[EA_000];
	res[EA_270] = res[EA_000];
	res[EA_315] = res[EA_000];
	return (res);
}

t_sprite	*util_create_sprite_by_name_suffix(t_engine *eng, char *name,
			char *suffix)
{
	t_sprite	*res;
	char		*full_name;

	full_name = ft_strjoin(name, suffix);
	res = util_create_sprite_by_name(eng, full_name);
	free(full_name);
	return (res);
}
