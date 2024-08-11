/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:28:23 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/11 12:23:22 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include "laag.h"
# include <math.h>

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_quadratic_root
{
	int		count;
	float	x1;
	float	x2;

}	t_roots;

typedef struct s_light_source
{
	t_vector	origin;
	float		intensity;
}	t_light_source;

typedef struct s_material
{
	t_vector	color;
	float		ambient;
	float		diffuse;
	float		specular;
	float		shine;
}	t_material;

typedef struct s_sphere
{
	t_vector	origin;
	float		r;
}	t_sphere;

typedef struct s_object
{
	void		*shape;
	t_material	material;
}	t_object;

typedef struct s_intersection
{
	t_object	object;
	float		time;
}	t_intersection;

/* ************************************************************************** */
// light.c
t_vector	vector_reflect(t_vector in, t_vector normal);
t_vector	lighting(t_material material, t_light_source light, t_vector point, t_vector eyev, t_vector normal);

/* ************************************************************************** */
// ray.c
t_vector	ray_position(t_ray ray, float t);
t_roots		quadratic_roots(float a, float b, float c);
t_roots		ray_sphere_intersect(t_ray ray, t_sphere sphere);

/* ************************************************************************** */

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_projectile
{
	t_vector	position;
	t_vector	velocity;
}	t_proj;

typedef struct s_environment
{
	t_vector	gravity;
	t_vector	wind;
}	t_env;

t_proj		tick(t_env env, t_proj proj);
t_vector	to_canvapos(t_vector u, int h);
int			v_inbound(t_vector u, int w, int h);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		put_vector(t_img *img, t_vector u, int color);
int			argb(t_uint8 a, t_uint8 r, t_uint8 g, t_uint8 b);

#endif
