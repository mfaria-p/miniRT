/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:32:42 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/09 15:33:08 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_spotlight	light_init(t_vec xyz, t_vec rgb, double intensity)
t_spotlight	light_init(t_light l)
{
	t_spotlight	light;

	light.origin = (t_vec){l.x, l.y, l.z};
	light.color = (t_vec){l.color.r, l.color.g, l.color.b};
	light.color = vec_scalar_prod(1 / 255.0, light.color);
	light.intensity = l.brightness;
	return (light);
}

t_spotlight	*light_translate(t_spotlight *light, t_vec dir, double shift)
{
	dir = vec_normalize(dir);
	dir = vec_scalar_prod(shift, dir);
	light->origin = vec_add(light->origin, dir);
	return (light);
}
