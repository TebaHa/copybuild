/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:19:27 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:48:15 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t num)
{
	char		*dst;
	const char	*src;
	size_t		i;

	dst = dest;
	src = source;
	i = 0;
	if (dest == NULL && source == NULL)
		return (NULL);
	if (dst <= src)
		while (i++ < num)
			*dst++ = *src++;
	else
	{
		dst = dst + num - 1;
		src = src + num - 1;
		while (i++ < num)
			*dst-- = *src--;
	}
	return (dest);
}
