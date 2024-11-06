/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:28:23 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/06 19:03:07 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "../libft/libft/libft.h"
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
	double		height;
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
	t_vector		axis;
}	t_object;

// increment to reallocate for intersections array
// minimizing nbr of allocations
# define INTERSECTION_BUFFER_STEP 2048

typedef struct s_intersection 
{
	double		t;
	t_object	*obj;
}	t_intersection;

typedef	struct s_intersections
{
	t_intersection	*hit;
	size_t			size;
	t_intersection	*is;
}	t_intersections;

typedef struct s_world
{
	t_vector		ray_origin;
	t_list	*objects;
	t_list	*lights;
	//t_camera		camera;
}	t_world;

/* ************************************************************************** */
// light.c
t_vector	vector_reflect(t_vector in, t_vector normal);
t_vector	lighting(t_material material, t_light_source light, t_vector point, t_vector eyev, t_vector normal);

/* ************************************************************************** */
// ray.c
t_vector	ray_position(t_ray ray, double t);
t_roots		quadratic_roots(double a, double b, double c);
t_roots		ray_object_intersect(t_ray ray, t_object object);
t_roots		ray_circle_intersect(t_ray ray, t_object object, double z);
t_roots		ray_plane_intersect(t_ray ray, t_object object, double z);
t_intersections	*ray_world_intersect(t_intersections *is, t_ray ray, t_world *world);

/* ************************************************************************** */
// shape.c
t_shape		shape_sphere_create(void);
t_shape		shape_cylinder_create(void);
t_shape		shape_cone_create(void);
t_shape		shape_plane_create(void);
t_shape		*shape_scale(t_shape *shape, double scale);
t_vector	normal_at(t_vector p, t_object object);


/* ************************************************************************** */
// object.c
t_object	*object_sphere_create(t_vector xyz, t_vector rgb, double d);
t_object	*object_cylinder_create(t_vector xyz, t_vector rgb, t_vector axis, double d, double h);
t_object	*object_plane_create(t_vector xyz, t_vector rgb, t_vector axis);
t_object	*object_cone_create(t_vector xyz, t_vector rgb, t_vector axis, double d, double h);
t_object	*object_height_new(t_object *obj, double height);
t_object	*object_coord_new(t_object *obj, t_vector coord);
t_object	*object_rot_new(t_object *obj, t_vector axis, double angle);
t_object	*object_coef_new(t_object *obj, t_vector new_coef);
t_object	*object_translate(t_object *obj, t_vector direction, double shift);
t_object	*object_rotate(t_object *obj, t_vector axis, double angle);
t_object	*object_scale(t_object *obj, double scale);

/* ************************************************************************** */
// world.c
t_world		*world_object_add(t_world *world, t_object *object);
t_world		*world_light_add(t_world *world, t_light_source *light);
void		world_destroy(t_world *world);
t_world		*world_init(t_world *world);

/* ************************************************************************** */
// intersections.c
t_intersections	*intersections_roots_add(t_intersections *is, t_roots xs, t_object *obj);
t_intersections	*intersections_init(t_intersections *is);

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
