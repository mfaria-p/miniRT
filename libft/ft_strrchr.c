/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:49:26 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/24 11:53:13 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// man strrchr
char	*ft_strrchr(const char *s, int c)
{
	char			*str;

	str = (char *) s;
	while (*str)
		str++;
	while (*str != c && str != (char *) s)
		str--;
	if (*str == c)
		return (str);
	else
		return (0);
}
