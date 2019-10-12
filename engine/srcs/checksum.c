/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:13:07 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 14:30:13 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

uint_least32_t crc_calculate(char *buf, size_t len)
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

void		checksum_check(char *buf, char **buff_splited, size_t len)
{
	int		i;
	char	**splitted_line;
	int		len2;

	i = 0;
	if (!ft_strnstr(buf, "crc:", len))
		util_parsing_error_wrong_crc();
	len2 = (int)(ft_strnstr(buf, "crc:", len) - buf);
	if (len2 < len - 20)
		util_parsing_error_wrong_crc();
//	ft_putnbr(len2);
	while (buff_splited[i])
	{
		if (ft_strwcmp(buff_splited[i], "crc:") == 0)
		{
			splitted_line = ft_strsplitwhitespaces(buff_splited[i]);
//			ft_putnbr(crc_calculate(buf, len2));
			if (!splitted_line[1] ||
			(crc_calculate(buf, len2) != ft_atoi(splitted_line[1])))
				util_parsing_error_wrong_crc();
			break;
		}
		i++;
	}
	if (!buff_splited[i])
		util_parsing_error_wrong_crc();
}
