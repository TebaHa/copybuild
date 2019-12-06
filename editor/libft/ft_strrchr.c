/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:03:33 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:30:46 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int symbol)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	while (i != -1)
	{
		if (string[i] == symbol)
			return ((char *)string + i);
		i--;
	}
	return (NULL);
}
