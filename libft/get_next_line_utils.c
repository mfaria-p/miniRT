/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:28:07 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/04 15:14:32 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strchr(char *str, int c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (c != 0 && str[i] == 0)
		i = -1;
	else if (c != 0 && str[i] == c)
		i++;
	return (i);
}

int	gnl_strcpy(char *dest, char *src, int start, int size)
{
	int	n;
	int	len_src;
	int	len_dest;

	len_src = gnl_strchr(src, 0);
	len_dest = gnl_strchr(dest, 0);
	if (size == 0 || start > len_dest)
		return (len_src);
	n = 0;
	while (n < size && *(src + n))
	{
		*(dest + start + n) = *(src + n);
		n++;
	}
	*(dest + start + n) = '\0';
	return (len_src);
}

char	*gnl_strjoin(char *str1, char *str2)
{
	int		str1_len;
	int		str2_len;
	char	*join;

	str1_len = gnl_strchr(str1, 0);
	str2_len = gnl_strchr(str2, 0);
	join = gnl_calloc(str1_len + str2_len + 1);
	gnl_strcpy(join, str1, 0, str1_len);
	gnl_strcpy(join, str2, str1_len, str2_len);
	return (join);
}

void	*gnl_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	*gnl_calloc(int size)
{
	int		i;
	char	*ptr;

	ptr = malloc(size * sizeof(char));
	if (!ptr)
		return (gnl_free(ptr));
	i = 0;
	while (i < size)
		ptr[i++] = '\0';
	return (ptr);
}
