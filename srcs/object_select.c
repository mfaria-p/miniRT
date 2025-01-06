/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:03:07 by mfaria-p          #+#    #+#             */
/*   Updated: 2025/01/06 14:05:27 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec	obj_select_aux(t_world *w, int x, int y)
{
	t_vec		p;
	double		scalar;
	t_vec		aux;

	p = vec_normalize(mat_vec_prod(w->cam.rmat, w->cam.axis));
	scalar = (x - w->cam.hsize / 2) * w->cam.pixel_size / w->cam.scale;
	aux = mat_vec_prod(w->cam.rmat, vec_scalar_prod(-1, w->cam.left));
	p = vec_add(p, vec_scalar_prod(scalar, vec_normalize(aux)));
	scalar = (y - w->cam.vsize / 2) * w->cam.pixel_size / w->cam.scale;
	aux = mat_vec_prod(w->cam.rmat, vec_scalar_prod(-1, w->cam.up));
	p = vec_add(p, vec_scalar_prod(scalar, vec_normalize(aux)));
	return (p);
}

t_obj	*obj_select(t_world *w, int x, int y)
{
	t_ray		ray;
	t_touches	is;
	t_obj		*selected;
	t_vec		p;

	selected = NULL;
	ray.origin = w->cam.origin;
	p = obj_select_aux(w, x, y);
	ray.dir = vec_normalize(p);
	touches_init(&is);
	ray_world_hits(&is, ray, w);
	if (is.hit)
		selected = is.hit->obj;
	free(is.is);
	return (selected);
}
