/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:36:00 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 18:55:51 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

int			main(int argc, char **argv)
{
	int		i;
	if (argc < 2)
		ft_putendl("Usage: ./checksum lvl_file");
	i = 1;
	while (i < argc)
	{
		check_and_add_crc(argv[i]);
		i++;
	}
}

void 		check_and_add_crc(char *filename)
{
	int		fd;
	int		number;
	int 	find;
	char	*buff;
	char	**splitedbuff;

	fd = open(filename, O_RDWR);
	buff = (char*)malloc(sizeof(char) * 10000);
	if (fd < 2)
		exit(EDITOR_ERROR);
	number = read(fd, buff, 10000);
	buff[number] = '\0';
	close(fd);
	splitedbuff = ft_strsplit(buff, '\n');
	find = find_checksum(buff, splitedbuff, number);
	if (find == CRC_OK)
	{
		ft_putstr(filename);
		ft_putendl(" have proper checksum!");
	}
	else
	{
		ft_putstr(filename);
		ft_putendl(" have incorrect checksum!");
	}
	util_release_char_matrix(splitedbuff);
	free(buff);
}

int 		find_checksum(char *buf, char **splitedbuff, size_t len)
{
	int		i;
	char	**splitted_line;
	int		len2;
	int 	crc_count;

	i = 0;
	if (!ft_strnstr(buf, "crc:", len))
		return(CRC_MISSING);
	len2 = (int)(ft_strnstr(buf, "crc:", len) - buf);
	if (len2 < len - 20)
		return(CRC_MULTIPLE);
//	ft_putnbr(len2);
	crc_count = 0;
	while (splitedbuff[i])
	{
		if (ft_strwcmp(splitedbuff[i], "crc:") == 0)
		{
			splitted_line = ft_strsplitwhitespaces(splitedbuff[i]);
//			ft_putnbr(crc_calculate(buf, len2));
			if (!splitted_line[1])
				return(CRC_MISSING);
			else if (crc_calculate(buf, len2) == ft_atoi(splitted_line[1]))
				crc_count++;
			else
				return (CRC_INCORRECT);
		}
		i++;
	}
	if (crc_count > 1)
		return(CRC_MULTIPLE);
	return(CRC_OK);
}
