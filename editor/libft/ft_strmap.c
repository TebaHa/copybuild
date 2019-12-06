/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:52:43 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:20:52 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*arr;
	size_t	i;
	size_t	count;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i++] != '\0')
		if (f(s[i - 1]))
			count++;
	i = 0;
	arr = ft_strnew(count);
	if (arr == NULL)
		return (NULL);
	count = 0;
	while (s[i++] != '\0')
		if (f(s[i - 1]))
			arr[count++] = f(s[i - 1]);
	return (arr);
}
