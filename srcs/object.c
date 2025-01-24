/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:59:01 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/24 14:38:52 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*obj_translate(t_obj *obj, t_vec dir, double shift)
{
	obj->translation.x = obj->translation.x + shift * dir.x;
	obj->translation.y = obj->translation.y + shift * dir.y;
	obj->translation.z = obj->translation.z + shift * dir.z;
	return (obj);
}

t_obj	*obj_rotate(t_obj *obj, t_vec euler)
{
	obj->rmat = mat_rotate_euler(obj->rmat, euler);
	obj->axis = mat_vec_prod(obj->rmat, (t_vec){0, 0, 1});
	return (obj);
}

t_obj	*obj_scale(t_obj *obj, double scale)
{
	if (obj->shape.type == PLANE)
		return (obj);
	obj->shape.scale *= scale;
	obj->shape.sradius *= scale * scale;
	return (obj);
}

t_obj	*obj_new_height(t_obj *obj, double height)
{
	if (obj->shape.type == CYLINDER)
		obj->shape.height = height;
	return (obj);
}
