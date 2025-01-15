/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:03:16 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/15 16:05:33 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	light_aux(t_phong *p, t_material mat, t_spotlight light, t_hit hit)
{
	t_vec	reflectv;
	double	cos_reflect_eye;
	double	factor;
	double	spec_aux;	
	t_vec	lightv;

	lightv = vec_normalize(vec_subtract(light.origin, hit.point));
	reflectv = vec_reflect(vec_scalar_prod(-1, lightv), hit.normal);
	cos_reflect_eye = vec_cosine(reflectv, hit.eyev);
	if (cos_reflect_eye > 0)
	{
		factor = pow(cos_reflect_eye, mat.shine);
		spec_aux = light.intensity * mat.spec * factor;
		p->spec = (t_vec){spec_aux, spec_aux, spec_aux};
	}
	else
		p->spec = (t_vec){0, 0, 0};
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
		cos_light_normal = vec_cosine(lightv, hit.normal);
		if (cos_light_normal >= 0)
		{
			phong.dif = vec_scalar_prod(mat.dif * cos_light_normal, color);
			light_aux(&phong, mat, light, hit);
		}
	}
	return (phong);
}
