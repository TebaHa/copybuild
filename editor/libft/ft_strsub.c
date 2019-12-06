/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 10:48:20 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:22:39 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	int		copy_len;

	buf = ft_strnew(len);
	if (buf == NULL || s == NULL)
		return (NULL);
	s += start;
	copy_len = 0;
	while (len-- && *s != '\0')
	{
		*buf++ = *s++;
		copy_len++;
	}
	return (buf - copy_len);
}
