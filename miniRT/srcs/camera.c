/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:42:15 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/04 15:08:17 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_for_pixel(t_cam *cam, int x, int y)
{
	double	x_offset;
	double	y_offset;
	double	world_xy[2];
	t_vec	pixel;
	t_ray	ray;

	x_offset = ((double)x - cam->hsize / (2 * cam->scale) + (cam->scale / 2.0));
	y_offset = ((double)y - cam->vsize / (2 * cam->scale) + (cam->scale / 2.0));
	world_xy[0] = x_offset * cam->pixel_size;
	world_xy[1] = -y_offset * cam->pixel_size;
	pixel = (t_vec){world_xy[0], world_xy[1], 3 - (((int)cam->scale + 2) % 3)};
	pixel = vec_rotate(pixel, cam->rotation.axis, cam->rotation.angle);
	pixel = vec_add(pixel, cam->origin);
	ray.origin = cam->origin;
	ray.dir = vec_normalize(vec_subtract(pixel, ray.origin));
	return (ray);
}

static t_img	*my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
	return (img);
}

static int	color_rgb(t_vec color)
{
	int	r;
	int	g;
	int	b;

	r = 0xFF * color.x;
	g = 0xFF * color.y;
	b = 0xFF * color.z;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (r << 16 | g << 8 | b);
	return (0xFF << 24 | r << 16 | g << 8 | b);
}

t_vec	color_blend(t_vec c1, t_vec c2)
{
	return ((t_vec){c1.x * c2.x, c1.y * c2.y, c1.z * c2.z});
}

t_img	*render(t_img *img, t_cam *cam, t_world *world)
{
	int		xy[2];
	int		xx;
	int		yy;
	int		color;
	t_ray	ray;

	xy[1] = 0;
	while (xy[1] < cam->vsize / cam->scale)
	{
		xy[0] = 0;
		while (xy[0] < cam->hsize / cam->scale)
		{
			ray = ray_for_pixel(cam, xy[0], xy[1]);
			color = color_rgb(color_at(world, ray));
			yy = xy[1] * cam->scale;
			while (yy < xy[1] * cam->scale + cam->scale)
			{
				xx = xy[0] * cam->scale;
				while (xx < xy[0] * cam->scale + cam->scale)
				{
					my_mlx_pixel_put(img, xx, yy, color);
					xx++;
				}
				yy++;
			}
			(xy[0])++;
		}
		(xy[1])++;
	}
	return (img);
}
