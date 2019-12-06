/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 12:01:24 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:33:19 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len_src;
	char	*dest;

	len_src = 0;
	while (src[len_src])
		len_src++;
	dest = (char *)malloc(len_src * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	len_src = 0;
	while (src[len_src++])
		dest[len_src - 1] = src[len_src - 1];
	dest[len_src - 1] = '\0';
	return (dest);
}
