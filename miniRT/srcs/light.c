/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:03:16 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 15:35:38 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"
#include "minirt.h"

t_light_source	light_init(t_vector xyz, t_vector rgb, double intensity)
{
	t_light_source	light;

	light.origin = xyz;
	light.color = rgb;
	light.intensity = intensity;
	return (light);
}

t_vector	vector_reflect(t_vector in, t_vector normal)
{
	return (vector_subtract(in, vector_scalar_product(2 * vector_dot_product(in, normal), normal)));
}

t_vector	color_blend(t_vector c1, t_vector c2)
{
	return ((t_vector){c1.x * c2.x, c1.y * c2.y, c1.z * c2.z});
}

t_phong	lighting(t_material material, t_light_source light, t_vector point, t_vector eyev, t_vector normal, int shadow)
{
	t_vector	color;
	t_vector	lightv;
	t_vector	ambient;
	double		cos_light_normal;
	t_vector	diffuse;
	double		specular_aux;	
	t_vector	specular;
	t_vector	reflectv;
	double		cos_reflect_eye;
	double		factor;

	color = vector_scalar_product(light.intensity, material.color);
	lightv = vector_normalize(vector_subtract(light.origin, point));
	ambient = vector_scalar_product(material.ambient, color);
	diffuse = (t_vector){0, 0, 0};
	specular = (t_vector){0, 0, 0};
	if (!shadow)
	{
		normal = vector_normalize(normal);
		cos_light_normal = vector_dot_product(lightv, normal);
		if (cos_light_normal >= 0)
		{
			diffuse = vector_scalar_product(material.diffuse * cos_light_normal, color);
			reflectv = vector_reflect(vector_scalar_product(-1, lightv), normal);
			cos_reflect_eye = vector_dot_product(reflectv, eyev);
			if (cos_reflect_eye <= 0)
				specular = (t_vector){0, 0, 0};
			else
			{
				factor = pow(cos_reflect_eye, material.shine);
				specular_aux = light.intensity * material.specular * factor;
				specular = (t_vector){specular_aux, specular_aux, specular_aux};
			}
		}
	}
	return ((t_phong){ambient, diffuse, specular});
}

t_light_source	*light_translate(t_light_source *light, t_vector direction, double shift)
{
	direction = vector_normalize(direction);
	direction = vector_scalar_product(shift, direction);
	light->origin = vector_add(light->origin, direction);
	return (light);
}
