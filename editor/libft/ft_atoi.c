/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:47:46 by djast             #+#    #+#             */
/*   Updated: 2019/06/08 14:03:34 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	size;
	int	result;
	int	neg;

	result = 0;
	size = 0;
	neg = 0;
	while (str[size] == ' ' || (str[size] >= 9 && str[size] <= 13))
		size++;
	if (str[size] == '-')
		neg = 1;
	if (str[size] == '-' || str[size] == '+')
		size++;
	while (str[size] >= 48 && str[size] <= 57)
		result = result * 10 + (str[size++] - 48);
	if (neg)
		return (-result);
	else
		return (result);
}
