/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:56:00 by djast             #+#    #+#             */
/*   Updated: 2018/12/18 16:02:00 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (big[i] != '\0')
	{
		j = 0;
		while (lit[j] == big[i + j] && i + j < len)
		{
			if (lit[j + 1] == '\0')
				return ((char *)(big + i));
			j++;
		}
		i++;
	}
	if (lit[0] == '\0')
		return ((char *)big);
	return (NULL);
}
