/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_point_math.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:55:49 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/05 22:46:42 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		clearbuf(void *dst, long c, long a)
{
	long	*ptr;

	ptr = (long *)dst;
	while(c-- > 0)
		*(ptr++) = a;
}

void		clearbufbyte(void *dst, long c, long a)
{
	char	*ptr;
	long	m[4];
	long	n[4];
	long	z;

	z = 0;
	*m = (long [4]){0xffl, 0xff00l, 0xff0000l, 0xff000000l};
	*n = (long [4]){0, 8, 16, 24};
	ptr = (char *)dst;
	while (c-- > 0)
	{
		*(ptr++) = (char)((a & m[z]) >> n[z]);
		z = (z + 1) & 3;
	}
}

void		copybuf(void *src, void *dst, long c)
{
	long	*ptr;
	long	*qtr;

	ptr = (long *)src;
	qtr = (long *)dst;
	while (c-- > 0)
		*(qtr++) = *(ptr++);
}

void		copybufbyte(void *src, void *dst, long c)
{
	char	*ptr;
	char	*qtr;

	ptr = (char *)src;
	qtr = (char *)dst;
	while (c-- > 0)
		*(qtr++) = *(ptr--);
}

void		qinterpolatedown16(long *bptr, long num, long val, long add)
{
	long	i;
	long	*ptr;

	ptr = bptr;
	i = 0;
	while (i < num)
	{
		ptr[i] = (val >> 16);
		val += add;
		i++;
	}
}

void		qinterpolatedown16short(long *bptr, long num, long val, long add)
{
	long	i;
	short	*ptr;

	ptr = (short *)bptr;
	i = 0;
	while (i < num)
	{
		ptr[i] = (short)(val >> 16);
		val += add;
		i++;
	}
}
