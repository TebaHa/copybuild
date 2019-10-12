/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:35:09 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 18:21:37 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# include <libft.h>
# include <unistd.h>
# include <math.h>
# include <engine.h>
# define EDITOR_H
# define EDITOR_ERROR 80

typedef enum		e_crc_state
{
	CRC_MISSING,
	CRC_INCORRECT,
	CRC_MULTIPLE,
	CRC_OK
}					t_crc_state;

void 		check_and_add_crc(char *filename);
int 		find_checksum(char *buf, char **buff_splited, size_t len);

#endif
