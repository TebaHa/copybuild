/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 11:06:32 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:38:18 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dst1;
	const unsigned char	*src1;

	src1 = src;
	dst1 = dst;
	while (n)
	{
		*dst1++ = *src1;
		if (*src1 == (unsigned char)c)
			return (dst1);
		src1++;
		n--;
	}
	return (NULL);
}
