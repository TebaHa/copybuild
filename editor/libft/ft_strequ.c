/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 10:35:49 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:33:31 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int	res;

	if ((s1 == NULL) && (s2 == NULL))
		return (1);
	if ((s1 == NULL) || (s2 == NULL))
		return (0);
	res = ft_strcmp(s1, s2);
	return (res != 0 ? 0 : 1);
}
