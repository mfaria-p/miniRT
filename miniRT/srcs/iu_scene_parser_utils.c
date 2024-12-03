/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_parser_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:16:59 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 01:21:32 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_int(const char **str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num * sign);
}

float	parse_float(const char **str)
{
	float	result;
	float	factor;
	int		sign;

	result = 0.0;
	factor = 1.0;
	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			factor *= 0.1f;
			result = result + (**str - '0') * (factor);
			(*str)++;
		}
	}
	return (result * sign);
}

void	skip_spaces(const char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

void	parse_color(const char **str, t_color *color, t_scenehe *scene)
{
	color->r = parse_int(str);
	if (color->r < 0 || color->r > 255)
		ft_error("Color R out of range [0, 255]", scene, EXIT_FAILURE);
	(*str)++;
	color->g = parse_int(str);
	if (color->g < 0 || color->g > 255)
		ft_error("Color G out of range [0, 255]", scene, EXIT_FAILURE);
	(*str)++;
	color->b = parse_int(str);
	if (color->b < 0 || color->b > 255)
		ft_error("Color B out of range [0, 255]", scene, EXIT_FAILURE);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	unsigned char *d;
	unsigned char *s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}