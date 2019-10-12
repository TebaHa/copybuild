/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:36:00 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 22:45:25 by fsmith           ###   ########.fr       */
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

int 		check_and_add_crc(char *filename)
{
	int		fd;
	int		number;
	int 	find;
	char	*buff;
	char	**splitedbuff;

	if ((fd = open(filename, O_RDWR)) < 0)
	{
		message_error_crc(filename, "can't read file!");
		return (0);
	}
	buff = (char*)malloc(sizeof(char) * 10000);
	if (fd < 2)
		exit(EDITOR_ERROR);
	number = read(fd, buff, 10000);
	buff[number] = '\0';
	splitedbuff = ft_strsplit(buff, '\n');
	find = checksum_check(buff, splitedbuff, number);
	if (find == CRC_OK)
		message_nice_crc(filename, "have proper checksum!");
	else if (find == CRC_INCORRECT)
		message_error_crc(filename, "have incorrect checksum!");
	else if (find == CRC_MULTIPLE)
		message_error_crc(filename, "have multiple checksum!");
	else if (find == CRC_NOT_IN_END)
		message_error_crc(filename, "checksum not in the end of file!");
	else if (find == CRC_ZERO)
		message_error_crc(filename, "checksum with empty line!");
	else if (find == CRC_MISSING)
	{
		if (!add_checksum(fd, buff, number))
			message_error_crc(filename, "can't write to file!");
		else
			message_nice_crc(filename, "crc added!");
	}
	close(fd);
	util_release_char_matrix(splitedbuff);
	free(buff);
	return (0);
}

int 		add_checksum(int fd, char *buf, size_t len)
{
	char 	*crc;

	if (ft_strncmp(&buf[len - 1], "\n", 1) != 0)
	{
		write(fd, "\n", 1);
	}
	if (!write(fd, "crc: ", 5))
		return (0);
	crc = ft_itoa(crc_calculate(buf, len));
	write(fd, crc, ft_strlen(crc));
	free(crc);
	return (1);
}

void	message_nice_crc(char *filename, char *result)
{
	ft_putstr(filename);
	ft_putstr(" OK: ");
	ft_putendl(result);
}

void	message_error_crc(char *filename, char *problem)
{
	ft_putstr(filename);
	ft_putstr(" KO: ");
	ft_putendl(problem);
}

