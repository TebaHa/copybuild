/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:35:09 by fsmith            #+#    #+#             */
/*   Updated: 2019/10/12 22:45:25 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include <libft.h>
# include <unistd.h>
# include <math.h>
# include <engine.h>
# define EDITOR_ERROR 80

int			crc_check_and_add(char *filename);
int			crc_add(int fd, char *buf, size_t len);
void		crc_message_ok(char *filename, char *result);
void		crc_message_error(char *filename, char *problem);
void		crc_analyse(int fd, int number, char *buff, char *filename);

#endif
