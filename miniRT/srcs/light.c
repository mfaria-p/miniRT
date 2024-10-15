/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:03:16 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/15 20:25:41 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"
#include "minirt.h"

t_vector	vector_reflect(t_vector in, t_vector normal)
{
	return (vector_subtract(in, vector_scalar_product(2 * vector_dot_product(in, normal), normal)));
}

t_vector	color_blend(t_vector c1, t_vector c2)
{
	return ((t_vector){c1.x * c2.x, c1.y * c2.y, c1.z * c2.z, 1});
}

t_vector	lighting(t_material material, t_light_source light, t_vector point, t_vector eyev, t_vector normal)
{
	t_vector	color;
	t_vector	lightv;
	t_vector	ambient;
	float		cos_light_normal;
	t_vector	diffuse;
	float		specular_aux;	
	t_vector	specular;
	t_vector	reflectv;
	float		cos_reflect_eye;
	float		factor;

	color = vector_scalar_product(light.intensity, material.color);
	lightv = vector_normalize(vector_subtract(light.origin, point));
	ambient = vector_scalar_product(material.ambient, color);
	normal = vector_normalize(normal);
	cos_light_normal = vector_dot_product(lightv, normal);
	if (cos_light_normal < 0)
	{
		diffuse = (t_vector){0, 0, 0, 1};
		specular = (t_vector){0, 0, 0, 1};
	}
	else
	{
		diffuse = vector_scalar_product(material.diffuse * cos_light_normal, color);
		reflectv = vector_reflect(vector_scalar_product(-1, lightv), normal);
		cos_reflect_eye = vector_dot_product(reflectv, eyev);
		if (cos_reflect_eye <= 0)
			specular = (t_vector){0, 0, 0, 1};
		else
		{
			factor = pow(cos_reflect_eye, material.shine);
			specular_aux = light.intensity * material.specular * factor;
			specular = (t_vector){specular_aux, specular_aux, specular_aux, 1};
		}
	}
	return (vector_add(vector_add(ambient, diffuse), specular));
}
