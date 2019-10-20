/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_package.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:28:46 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 18:57:28 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_pack_resources(int loudness, int cleaning)
{
	if (system("test -d "RESOURCES_FOLDER) == 0)
	{
		if (system("test -f "RESOURCES_PACK) == 0)
			system("rm -rf " RESOURCES_PACK);
		if (system("tar -cf " RESOURCES_PACK " " RESOURCES_FOLDER) == 0)
		{
			if (loudness == MODE_LOUD)
				ft_putendl("Resources successfully packed");
			if (cleaning == MODE_CLEANING)
				engine_remove_resources_folder(loudness);
		}
	}
	else
	{
		ft_putendl("No resources");
		exit(PACKAGE_ERROR);
	}
}

void		engine_unpack_resources(int loudness, int cleaning)
{
	if (system("test -f "RESOURCES_PACK) == 0)
	{
		if (system("test -d "RESOURCES_FOLDER) == 0)
			system("rm -rf " RESOURCES_FOLDER);
		if (system("tar -xf " RESOURCES_PACK " " RESOURCES_FOLDER) == 0)
		{
			if (loudness == MODE_LOUD)
				ft_putendl("Resources successfully unpacked");
			if (cleaning == MODE_CLEANING)
				engine_remove_resources_pack(loudness);
		}
	}
	else
	{
		ft_putendl("No archieve");
		exit(PACKAGE_ERROR);
	}
}

void		engine_remove_resources_folder(int loudness)
{
	system("rm -rf " RESOURCES_FOLDER);
	if (loudness == MODE_LOUD)
		ft_putendl("Resources folder deleted");
}

void		engine_remove_resources_pack(int loudness)
{
	system("rm -rf " RESOURCES_PACK);
	if (loudness == MODE_LOUD)
		ft_putendl("Resources package deleted");
}
