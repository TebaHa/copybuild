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
		ft_putendl("Usage: ./DoomEditor lvl_file\n"
					"       ./DoomEditor pack\n"
					"       ./DoomEditor unpack");
	if (argc == 2 && (ft_strcmp(argv[1], "unpack") == 0))
		engine_unpack_resources(MODE_LOUD, MODE_LEAVE);
	else if (argc == 2 && (ft_strcmp(argv[1], "pack") == 0))
		engine_pack_resources(MODE_LOUD, MODE_CLEANING);
	else
	{
		i = 1;
		while (i < argc)
		{
			crc_check_and_add(argv[i]);
			i++;
		}
	}
}

int			crc_check_and_add(char *filename)
{
	int		fd;
	int		number;
	char	*buff;

	if ((fd = open(filename, O_RDWR)) < 0)
	{
		crc_message_error(filename, "can't read file!");
		return (0);
	}
	buff = (char*)malloc(sizeof(char) * 10000);
	if (fd < 2)
		close_game(EDITOR_ERROR);
	number = read(fd, buff, 10000);
	buff[number] = '\0';
	if (ft_strncmp(buff, "Map", 3) == 0)
		crc_analyse(fd, number, buff, filename);
	else
		crc_message_error(filename, "not map file");
	close(fd);
	free(buff);
	return (0);
}

void		crc_analyse(int fd, int number, char *buff, char *filename)
{
	int		crc;
	char	**splitedbuff;

	splitedbuff = ft_strsplit(buff, '\n');
	crc = checksum_check(buff, splitedbuff, number);
	if (crc == CRC_OK)
		crc_message_ok(filename, "have proper checksum!");
	else if (crc == CRC_INCORRECT)
		crc_message_error(filename, "have incorrect checksum!");
	else if (crc == CRC_MULTIPLE)
		crc_message_error(filename, "have multiple checksum!");
	else if (crc == CRC_NOT_IN_END)
		crc_message_error(filename, "checksum not in the end of file!");
	else if (crc == CRC_ZERO)
		crc_message_error(filename, "checksum with empty line!");
	else if (crc == CRC_MISSING)
	{
		if (!crc_add(fd, buff, number))
			crc_message_error(filename, "can't write to file!");
		else
			crc_message_ok(filename, "crc added!");
	}
	util_release_char_matrix(splitedbuff);
}

int			crc_add(int fd, char *buf, size_t len)
{
	char	*crc;

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
