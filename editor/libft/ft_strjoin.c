/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:05:15 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:19:56 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	buf = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (buf == NULL)
		return (NULL);
	ft_strcpy(buf, (char *)s1);
	buf += ft_strlen(s1);
	ft_strcpy(buf, (char *)s2);
	return (buf - ft_strlen(s1));
}
