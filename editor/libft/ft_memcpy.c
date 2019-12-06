/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:27:23 by djast             #+#    #+#             */
/*   Updated: 2018/12/18 16:02:47 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t num)
{
	size_t		i;
	char		*dst;
	const char	*src;

	if (dest == NULL && source == NULL)
		return (NULL);
	src = source;
	dst = dest;
	i = 0;
	while (i++ < num)
		*dst++ = *src++;
	return (dest);
}
