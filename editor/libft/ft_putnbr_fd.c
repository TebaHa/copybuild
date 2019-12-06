/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:55:18 by djast             #+#    #+#             */
/*   Updated: 2018/12/11 19:34:31 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_size(int n)
{
	int count;

	count = 0;
	while ((n = n / 10) != 0)
		count++;
	return (count + 1);
}

static int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	return (nb * ft_recursive_power(nb, power - 1));
}

void		ft_putnbr_fd(int n, int fd)
{
	int	size;
	int	mno;

	size = ft_num_size(n) - 1;
	mno = ft_recursive_power(10, size);
	n < 0 ? ft_putchar_fd('-', fd) : NULL;
	while (mno != 0)
	{
		ft_putchar_fd(n > 0 ? n / mno + 48 : -(n / mno) + 48, fd);
		n %= mno;
		mno /= 10;
	}
}
