/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:13:07 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/11 19:13:16 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

uint_least32_t Crc32(unsigned char *buf, size_t len)
{
	uint_least32_t crc_table[256];
	uint_least32_t crc; int i, j;
	for (i = 0; i < 256; i++)
	{
		crc = i;
		for (j = 0; j < 8; j++)
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
		crc_table[i] = crc;
	};
	crc = 0xFFFFFFFFUL;
	while (len--)
		crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
	return crc ^ 0xFFFFFFFFUL;
}
