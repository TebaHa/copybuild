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
# include <libft.h>
# include <unistd.h>
# include <math.h>
# include <engine.h>
# define EDITOR_H
# define EDITOR_ERROR 80

int			check_and_add_crc(char *filename);
int			add_checksum(int fd, char *buf, size_t len);
void		message_nice_crc(char *filename, char *result);
void		message_error_crc(char *filename, char *problem);
void		analyse_crc(int fd, int number, char *buff, char *filename);

#endif
