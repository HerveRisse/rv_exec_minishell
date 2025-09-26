/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saif-eddine <saif-eddine@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:49:56 by sm-gaidi          #+#    #+#             */
/*   Updated: 2025/05/20 23:31:04 by saif-eddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd, int finish);
size_t	get_len(const char *s, int c);
char	*find_ch(char *remainder, int c);
char	*str_joined(const char *s1, const char *s2, size_t len_1, size_t len_2);
char	*get_new_line(char *remainder);
char	*new_remainder(char **remainder, size_t start);
char	*read_file(int fd, char **remainder);
void	clear_buffer(char *buffer);
int		check_endfile(int read_bytes, char buffer[BUFFER_SIZE],
			char **remainder);

#endif
