/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:59:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/06 14:34:33 by mfaria-p         ###   ########.fr       */
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

t_obj	*obj_rotate(t_obj *obj, t_vec axis, double angle)
{
	obj->axis = vec_rotate_ax(obj->axis, axis, angle);
	obj->rotation.axis = vec_cross_prod(obj->axis, (t_vec){0, 0, 1});
	obj->rotation.angle = acos(vec_cosine(obj->axis, (t_vec){0, 0, 1}));
	return (obj);
}

t_obj	*obj_scale(t_obj *obj, double scale)
{
	if (obj->shape.type == PLANE)
		return (obj);
	obj->shape.scale *= scale;
	if (obj->shape.type == CONE)
		obj->shape.coef.z *= scale;
	else if (obj->shape.type == SPHERE || obj->shape.type == CYLINDER)
		obj->shape.constant *= scale;
	return (obj);
}

t_obj	*obj_new_height(t_obj *obj, double height)
{
	if (obj->shape.type == CYLINDER)
		obj->shape.height = height;
	return (obj);
}
