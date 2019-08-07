/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitwhitespaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:30:57 by fsmith            #+#    #+#             */
/*   Updated: 2019/08/07 22:04:05 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

//int		ft_countwords_whitespaces(char const *s)
//{
//	int			cnt;
//	const char	*l_comma;
//	const char	*tmp;
//	int			f;
//
//	tmp = s;
//	l_comma = 0;
//	cnt = 0;
//	f = 0;
//	while (*tmp)
//	{
//		if ((*tmp == ' ' || *tmp == '\t') && f == 0)
//		{
//			cnt++;
//			f = 1;
//			l_comma = tmp;
//		}
//		else if (*tmp != ' ' && *tmp != '\t' && f == 1)
//			f = 0;
//		tmp++;
//	}
//	cnt += l_comma < (s + ft_strlen(s) - 1);
//	cnt++;
//	return (cnt);
//}

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


static char		*ft_cutword_whitespaces(char const *s, size_t i)
{
	char	*word;
	size_t	end;
	size_t	l;

	l = 0;
	end = i + 1;
	while (s[end] && s[end] != ' ' && s[end] != '\t')
		end++;
	word = (char *)ft_strnew(end - i);
	if (word == NULL)
		return (NULL);
	while (s[i] && i < end)
	{
		word[l++] = s[i];
		i++;
	}
	return (word);
}

static void		ft_putnull(char **res, int cnt)
{
	if (cnt > 1)
	{
		free(res[cnt - 1]);
		res[cnt - 1] = NULL;
	}
	else
	{
		free(res[cnt]);
		res[cnt] = NULL;
	}
}

char			**ft_strsplitwhitespaces(char const *s)
{
	char	**res;
	int		cnt;
	int		words;
	size_t	i;

	if (s)
	{
		i = 0;
		cnt = 0;
		words = ft_countwords_whitespaces(s);
		res = (char **)ft_memalloc(sizeof(char **) * words);
		if (res == NULL)
			return (NULL);
		while (words-- > 0)
		{
			while (s[i] && (s[i] == ' ' || s[i] == '\t'))
				i++;
			res[cnt++] = ft_cutword_whitespaces(s, i);
			while (s[i] && s[i] != ' ' && s[i] != '\t')
				i++;
		}
		ft_putnull(res, cnt);
		return (res);
	}
	return (NULL);
}
