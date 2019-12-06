/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 13:11:19 by djast             #+#    #+#             */
/*   Updated: 2019/01/03 15:24:47 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_lines(const int fd, char **my_line)
{
	int		size;
	char	*buf;
	char	*old_str;

	size = 1;
	if ((buf = ft_strnew(BUFF_SIZE)) == NULL)
		return (NULL);
	while ((ft_strchr(*my_line, '\n') == NULL) && size > 0)
	{
		if ((size = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[size] = '\0';
			old_str = *my_line;
			if ((*my_line = ft_strjoin(*my_line, buf)) == NULL)
				return (NULL);
			free(old_str);
		}
	}
	free(buf);
	return (*my_line);
}

char	*parse_line(char **my_line)
{
	char *buf;
	char *old_str;

	old_str = NULL;
	buf = NULL;
	if (ft_strchr(*my_line, '\n') == NULL)
	{
		if ((buf = ft_strdup(*my_line)) == NULL)
			return (NULL);
		free(*my_line);
		*my_line = NULL;
	}
	else
	{
		if ((buf = ft_strsub(*my_line, 0,
			ft_strchr(*my_line, '\n') - *my_line)) == NULL)
			return (NULL);
		old_str = *my_line;
		if ((*my_line = ft_strdup(ft_strchr(*my_line, '\n') + 1)) == NULL)
			return (NULL);
		free(old_str);
	}
	return (buf);
}

int		get_next_line(const int fd, char **line)
{
	static char *my_line[10240];

	if (fd < 0 || fd > 10240 || line == NULL ||
		read(fd, NULL, 0) == -1 || BUFF_SIZE <= 0)
		return (-1);
	if (my_line[fd] == NULL)
	{
		if ((my_line[fd] = ft_strnew(0)) == NULL)
			return (-1);
	}
	if (read_lines(fd, &my_line[fd]) == NULL)
		return (-1);
	if (*my_line[fd])
	{
		if ((*line = parse_line(&my_line[fd])) == NULL)
			return (-1);
		return (1);
	}
	return (0);
}
