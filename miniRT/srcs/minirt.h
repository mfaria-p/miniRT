/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:28:23 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/02 18:04:36 by ecorona-         ###   ########.fr       */
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
	double	x1;
	double	x2;
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

enum e_shape_type
{
	SPHERE,
	CONE,
	CYLINDER,
	PLANE,
};

typedef struct s_shape
{
	int			type;
	t_vector	coefficients;
	double		bounds[2];
	double		constant;
	double		scale;
}	t_shape;

typedef struct s_object
{
	t_shape			shape;
	t_material		material;
	t_vector		translation;
	struct	s_rotation
	{
		t_vector	axis;
		double		angle;
	}				rotation;
}	t_object;

// will need a list of intersections
// should probably make a linked list
typedef struct s_intersection
{
	t_object	object;
	float		time;
}	t_intersection;

typedef struct	s_world
{
	t_object		*objects;
	t_light_source	*lights;
	//t_camera		camera;
}	t_world;

/* ************************************************************************** */
// light.c
t_vector	vector_reflect(t_vector in, t_vector normal);
t_vector	lighting(t_material material, t_light_source light, t_vector point, t_vector eyev, t_vector normal);

/* ************************************************************************** */
// ray.c
t_vector	ray_position(t_ray ray, float t);
t_roots		quadratic_roots(double a, double b, double c);
t_roots		ray_object_intersect(t_ray ray, t_object object);
t_roots		ray_circle_intersect(t_ray ray, t_object object, double z);
t_roots		ray_plane_intersect(t_ray ray, t_object object, double z);

/* ************************************************************************** */
// shape.c
t_shape		create_sphere(void);
t_shape		create_cylinder(void);
t_shape		create_cone(void);
t_shape		create_plane(void);
t_shape		*shape_scale(t_shape *shape, double scale);
t_vector	normal_at(t_vector p, t_object object);

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
