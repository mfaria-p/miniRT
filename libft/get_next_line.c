/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:28:31 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/04 15:14:34 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
ARGS:
	fd: The file descriptor to be read.
RETURN VALUE:
	The first line of the file as a string.
DESC:
	Reads a file and returns its first line.
*/
char	*get_next_line(int fd)
{
	static char	buf[1024][BUFFER_SIZE];
	char		*line;
	int			loop;

	if (fd < 0)
		return (NULL);
	line = NULL;
	loop = 1;
	if (*buf[fd])
		line = read_buf(buf[fd], &loop);
	while (loop)
	{
		line = read_fd(fd, buf[fd], line, &loop);
		if (!line)
			loop = 0;
	}
	return (line);
}

char	*read_buf(char *buf, int *loop)
{
	int		buf_len;
	int		new_line;
	char	*line;

	buf_len = gnl_strchr(buf, 0);
	new_line = gnl_strchr(buf, '\n');
	if (new_line > 0 && new_line <= buf_len)
	{
		line = gnl_calloc(new_line + 1);
		if (!line)
			return (NULL);
		gnl_strcpy(line, buf, 0, new_line);
		write_buf(buf, new_line, buf_len);
		*loop = 0;
	}
	else
	{
		line = gnl_calloc(buf_len + 1);
		if (!line)
			return (NULL);
		gnl_strcpy(line, buf, 0, buf_len);
		write_buf(buf, 0, 0);
	}
	return (line);
}

void	write_buf(char *buf, int start, int end)
{
	int	i;

	i = 0;
	while (start + i < end)
	{
		buf[i] = buf[start + i];
		i++;
	}
	while (i < BUFFER_SIZE)
		buf[i++] = '\0';
}

char	*read_fd(int fd, char *buf, char *line, int *loop)
{
	char	*temp;
	char	*aux;
	int		read_size;

	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size > 0)
	{
		aux = read_buf(buf, loop);
		temp = line;
		line = gnl_strjoin(line, aux);
		gnl_free(aux);
		gnl_free(temp);
		if (!line)
			return (NULL);
	}
	else
	{
		if (end_of_file(read_size, loop, line) < 0)
			return (NULL);
	}
	return (line);
}

int	end_of_file(int read_size, int *loop, char *line)
{
	*loop = 0;
	if (read_size < 0)
	{
		free(line);
		line = NULL;
		return (-1);
	}
	return (0);
}
