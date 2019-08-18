/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitwhitespaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:30:57 by fsmith            #+#    #+#             */
/*   Updated: 2019/08/18 15:14:17 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int			ft_countwords_whitespaces(char const *s)
{
	int		i;
	int		count;

	if (s)
	{
		i = 0;
		count = 0;
		while (s[i])
		{
			if ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
				i++;
			else
			{
				count++;
				while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
					i++;
			}
		}
		return (count);
	}
	return (0);
}

static char		**ft_strsplitwhitespaces_check(char const *s)
{
	char		**output;

	if (!s)
		return (NULL);
	if (!(output = (char **)malloc(sizeof(char *)
		* (ft_countwords_whitespaces(s) + 1))))
		return (NULL);
	return (output);
}

static void		*ft_freetab(char ***output, size_t err_word)
{
	size_t word;

	word = 0;
	while (word < err_word)
	{
		free((*output)[word]);
		word++;
	}
	free(*output);
	return (NULL);
}

char			**ft_strsplitwhitespaces(char const *s)
{
	size_t		i;
	size_t		pos;
	int			words;
	char		**output;

	if (!(output = ft_strsplitwhitespaces_check(s)))
		return (NULL);
	i = 0;
	pos = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			pos = ++i;
		else
			while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
			{
				if (s[i + 1] == ' ' || s[i + 1] == '\t' || s[i + 1] == '\0')
					if (!(output[words++] = ft_strsub(s, pos, (i + 1 - pos))))
						return (ft_freetab(&output, words));
				i++;
			}
	}
	output[words] = NULL;
	return (output);
}
