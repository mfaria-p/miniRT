/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:03:16 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:01:25 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"
#include "minirt.h"

t_spotlight	light_init(t_vec xyz, t_vec rgb, double intensity)
{
	t_spotlight	light;

	light.origin = xyz;
	light.color = rgb;
	light.intensity = intensity;
	return (light);
}

t_vec	vec_reflect(t_vec in, t_vec normal)
{
	return (vec_subtract(in, vec_scalar_prod(2 * vec_dot_prod(in, normal), normal)));
}

t_vec	color_blend(t_vec c1, t_vec c2)
{
	return ((t_vec){c1.x * c2.x, c1.y * c2.y, c1.z * c2.z});
}

t_phong	lighting(t_material material, t_spotlight light, t_vec point, t_vec eyev, t_vec normal, int shadow)
{
	t_vec	color;
	t_vec	lightv;
	t_vec	amb;
	double	cos_light_normal;
	t_vec	dif;
	double	spec_aux;	
	t_vec	spec;
	t_vec	reflectv;
	double	cos_reflect_eye;
	double	factor;

	color = vec_scalar_prod(light.intensity, material.color);
	lightv = vec_normalize(vec_subtract(light.origin, point));
	amb = vec_scalar_prod(material.amb, color);
	dif = (t_vec){0, 0, 0};
	spec = (t_vec){0, 0, 0};
	if (!shadow)
	{
		normal = vec_normalize(normal);
		cos_light_normal = vec_dot_prod(lightv, normal);
		if (cos_light_normal >= 0)
		{
			dif = vec_scalar_prod(material.dif * cos_light_normal, color);
			reflectv = vec_reflect(vec_scalar_prod(-1, lightv), normal);
			cos_reflect_eye = vec_dot_prod(reflectv, eyev);
			if (cos_reflect_eye <= 0)
				spec = (t_vec){0, 0, 0};
			else
			{
				factor = pow(cos_reflect_eye, material.shine);
				spec_aux = light.intensity * material.spec * factor;
				spec = (t_vec){spec_aux, spec_aux, spec_aux};
			}
		}
	}
	return ((t_phong){amb, dif, spec});
}

t_spotlight	*light_translate(t_spotlight *light, t_vec dir, double shift)
{
	dir = vec_normalize(dir);
	dir = vec_scalar_prod(shift, dir);
	light->origin = vec_add(light->origin, dir);
	return (light);
}
