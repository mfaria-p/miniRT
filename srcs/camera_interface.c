/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:28:56 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/24 14:31:04 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam	*cam_rescale(t_cam *cam, double new_scale)
{
	cam->pixel_size /= cam->scale;
	cam->scale = new_scale;
	cam->pixel_size *= cam->scale;
	return (cam);
}

t_cam	*cam_coord_new(t_cam *cam, t_vec coord)
{
	cam->origin = coord;
	return (cam);
}

t_cam	*cam_translate(t_cam *cam, t_vec dir, double shift)
{
	cam->origin.x = cam->origin.x + shift * dir.x;
	cam->origin.y = cam->origin.y + shift * dir.y;
	cam->origin.z = cam->origin.z + shift * dir.z;
	return (cam);
}

t_cam	*cam_rotate(t_cam *cam, t_vec euler)
{
	cam->rmat = mat_rotate_euler(cam->rmat, euler);
	cam->axis = mat_vec_prod(cam->rmat, (t_vec){0, 0, 1});
	cam->right = mat_vec_prod(cam->rmat, (t_vec){1, 0, 0});
	cam->up = mat_vec_prod(cam->rmat, (t_vec){0, 1, 0});
	return (cam);
}
