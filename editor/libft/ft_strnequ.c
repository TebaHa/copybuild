/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 10:45:31 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:31:51 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int	res;

	if ((s1 == NULL) && (s2 == NULL))
		return (1);
	if ((s1 == NULL) || (s2 == NULL))
		return (0);
	res = ft_strncmp(s1, s2, n);
	return (res != 0 ? 0 : 1);
}
