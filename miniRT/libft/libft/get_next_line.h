/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:26:53 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/04 15:14:33 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		gnl_strchr(char *str, int c);
int		gnl_strcpy(char *dest, char *src, int start, int size);
char	*read_buf(char *buf, int *loop);
void	write_buf(char *buf, int start, int end);
char	*read_fd(int fd, char *buf, char *line, int *loop);
char	*gnl_strjoin(char *str1, char *str2);
void	*gnl_free(void *ptr);
void	*gnl_calloc(int size);
int		end_of_file(int read_size, int *loop, char *line);

#endif
