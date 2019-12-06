/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:10:23 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:35:06 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int symbol)
{
	while (*string != '\0')
	{
		if (*string == symbol)
			return ((char *)string);
		string++;
	}
	if (symbol == '\0')
		return ((char *)string);
	return (NULL);
}
