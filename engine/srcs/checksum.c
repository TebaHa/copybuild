/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:13:07 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 22:46:23 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

uint_least32_t		crc_calculate(char *buf, size_t len)
{
	uint_least32_t	crc_table[256];
	uint_least32_t	crc;
	int				i;
	int				j;

	i = 0;
	while (i < 256)
	{
		crc = i;
		j = 0;
		while (j < 8)
		{
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
			j++;
		}
		crc_table[i] = crc;
		i++;
	}
	crc = 0xFFFFFFFFUL;
	while (len--)
		crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
	return (crc ^ 0xFFFFFFFFUL);
}

int					checksum_check(char *buf, char **buff_splited, size_t len)
{
	int		i;
	int		crc_pos;
	int		crc_count;
	int		result;

	i = 0;
	if (!ft_strnstr(buf, "crc:", len))
		return (CRC_MISSING);
	crc_pos = (int)(ft_strnstr(buf, "crc:", len) - buf);
	if (crc_pos < len - 20)
		return (CRC_NOT_IN_END);
	crc_count = 0;
	while (buff_splited[i])
	{
		result = checksum_check_line(buf, buff_splited[i], &crc_count, crc_pos);
		if (result != CRC_OK)
			return (result);
		i++;
	}
	if (crc_count > 1)
		return (CRC_MULTIPLE);
	return (CRC_OK);
}

int					checksum_check_line(char *buff, char *buff_splited,
					int *crc_count, int crc_pos)
{
	char	**splitted_line;

	if (ft_strwcmp(buff_splited, "crc:") == 0)
	{
		splitted_line = ft_strsplitwhitespaces(buff_splited);
		if (!splitted_line[1])
			return (CRC_ZERO);
		else if (crc_calculate(buff, crc_pos) == ft_atoi(splitted_line[1]))
			crc_count++;
		else
			return (CRC_INCORRECT);
		util_release_char_matrix(splitted_line);
	}
	return (CRC_OK);
}

void				util_parsing_error_wrong_crc(void)
{
	ft_putendl("Parsing error:");
	ft_putendl("Wrong checksum!");
	close_game(PARSING_ERROR);
}
