/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:16:18 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/09 20:39:44 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ARGS:
	c: The character to output.
	fd:	The file descriptor on which to write.
RETURN VALUE:
	None.
DESC:
	Outputs the character 'c' to the given file descriptor.
*/
void	ft_putchar_fd(char c, int fd)
{
	ssize_t	b;

	b = write(fd, &c, 1);
	(void)b;
}
