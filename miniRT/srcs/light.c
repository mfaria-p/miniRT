/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:03:16 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/04 15:08:10 by ecorona-         ###   ########.fr       */
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

t_vec	vec_reflect(t_vec in, t_vec n)
{
	return (vec_subtract(in, vec_scalar_prod(2 * vec_dot_prod(in, n), n)));
}

static void	light_aux(t_phong *p, t_material mat, t_spotlight light, t_hit hit)
{
	t_vec	reflectv;
	double	cos_reflect_eye;
	double	factor;
	double	spec_aux;	
	t_vec	lightv;

	lightv = vec_normalize(vec_subtract(light.origin, hit.point));
	reflectv = vec_reflect(vec_scalar_prod(-1, lightv), hit.normal);
	cos_reflect_eye = vec_dot_prod(reflectv, hit.eyev);
	if (cos_reflect_eye <= 0)
		p->spec = (t_vec){0, 0, 0};
	else
	{
		factor = pow(cos_reflect_eye, mat.shine);
		spec_aux = light.intensity * mat.spec * factor;
		p->spec = (t_vec){spec_aux, spec_aux, spec_aux};
	}
}

t_phong	lighting(t_material mat, t_spotlight light, t_hit hit, int shadow)
{
	t_vec	color;
	t_vec	lightv;
	t_phong	phong;
	double	cos_light_normal;

	color = vec_scalar_prod(light.intensity, mat.color);
	lightv = vec_normalize(vec_subtract(light.origin, hit.point));
	phong.amb = vec_scalar_prod(mat.amb, color);
	phong.dif = (t_vec){0, 0, 0};
	phong.spec = (t_vec){0, 0, 0};
	if (!shadow)
	{
		hit.normal = vec_normalize(hit.normal);
		cos_light_normal = vec_dot_prod(lightv, hit.normal);
		if (cos_light_normal >= 0)
		{
			phong.dif = vec_scalar_prod(mat.dif * cos_light_normal, color);
			light_aux(&phong, mat, light, hit);
		}
	}
	return (phong);
}

t_spotlight	*light_translate(t_spotlight *light, t_vec dir, double shift)
{
	dir = vec_normalize(dir);
	dir = vec_scalar_prod(shift, dir);
	light->origin = vec_add(light->origin, dir);
	return (light);
}
