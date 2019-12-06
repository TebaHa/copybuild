/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 13:51:28 by djast             #+#    #+#             */
/*   Updated: 2018/12/13 13:17:30 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*p1 = (const unsigned char *)s1;
	const unsigned char	*p2 = (const unsigned char *)s2;

	if (n == 0)
		return (0);
	while (*p1 == *p2 && n--)
	{
		if (*p1 == '\0')
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	if (n == 0)
		return (*(--p1) - *(--p2));
	return (*p1 - *p2);
}
