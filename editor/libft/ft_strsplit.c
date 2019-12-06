/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:56:43 by djast             #+#    #+#             */
/*   Updated: 2019/03/18 11:24:42 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			count_word(char const *s, char c)
{
	char	*s1;
	int		count;

	count = 0;
	if (s == NULL)
		return (0);
	s1 = (char *)s;
	while (*s1 != '\0')
	{
		while (*s1 == c && *s1 != '\0')
			s1++;
		if (*s1 != c && *s1 != '\0')
		{
			count++;
			while (*s1 != c && *s1 != '\0')
				s1++;
		}
	}
	return (count);
}

static char			**ft_del(char **buf, int size)
{
	int i;

	i = 0;
	while (i != size)
		free(buf[i++]);
	free(buf);
	return (NULL);
}

static char			**ft_fillarray(char *s1, char **buf, char c)
{
	int		end_word;
	int		i;

	i = 0;
	while (*s1 != '\0')
	{
		end_word = 0;
		while (*s1 == c && *s1 != '\0')
			s1++;
		if (*s1 == '\0')
			break ;
		while (*s1 != c && *s1 != '\0')
			s1 = s1 + end_word++ * 0 + 1;
		if ((buf[i] = ft_strnew(end_word)) == NULL)
			return (ft_del(buf, count_word(s1, c)));
		ft_strncpy(buf[i++], s1 - end_word, end_word);
	}
	buf[i] = NULL;
	return (buf);
}

char				**ft_strsplit(char const *s, char c)
{
	char	*s1;
	char	**buf;

	if (s == NULL)
		return (NULL);
	s1 = (char *)s;
	if ((buf = (char **)malloc(sizeof(buf) * (count_word(s, c) + 1))) == NULL)
		return (NULL);
	ft_fillarray(s1, buf, c);
	return (buf);
}
