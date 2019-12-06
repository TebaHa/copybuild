/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:19:07 by djast             #+#    #+#             */
/*   Updated: 2018/12/13 14:00:36 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*s1;
	int		size;
	int		start;

	if (s == NULL)
		return (NULL);
	s1 = (char *)s;
	start = 0;
	while (*s1 == ' ' || *s1 == '\n' || *s1 == '\t')
		s1 = s1 + start++ * 0 + 1;
	if (*s1 == '\0')
		return (s1 = ft_strnew(0));
	size = ft_strlen(s1);
	s1 += size - 1;
	while (*s1 == ' ' || *s1 == '\n' || *s1 == '\t')
		s1 = s1 + size-- * 0 - 1;
	s1 = ft_strsub(s, start, size);
	return (s1);
}
