/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_point_math.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:56:21 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/05 22:45:17 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_POINT_MATH_H
# define FIXED_POINT_MATH_H

void	clearbuf(void *dst, long c, long a);

void	clearbufbyte(void *dst, long c, long a);

void	copybuf(void *src, void *dst, long c);

void	copybufbyte(void *src, void *dst, long c);

void	copybufreverse(void *src, void *dst, long c);

void	qinterpolatedown16(long *bptr, long num, long val, long add);

void	qinterpolatedown16short(long *bptr, long num, long val, long add);

#endif
