/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:28:23 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/14 17:58:53 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define CANVAS_PIXEL 600

# include "../minilibx-linux/mlx.h"
# include "X11/X.h"
# include "libft.h"
# include "laag.h"
# include "iu_scene.h"
# include <math.h>

// color vec have values between 0 and 1

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_quadratic_root
{
	int		count;
	double	x1;
	double	x2;
}	t_roots;

// intensity is between [0,1]
typedef struct s_spotlight
{
	t_vec	origin;
	double	intensity;
	t_vec	color;
}	t_spotlight;

typedef struct s_phong
{
	t_vec	amb;
	t_vec	dif;
	t_vec	spec;
}	t_phong;

// all properties are between [0,1]
typedef struct s_material
{
	t_vec	color;
	double	amb;
	double	dif;
	double	spec;
	double	shine;
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
	int		type;
	double	height;
	double	sradius;
	double	scale;
}	t_shape;

typedef struct s_obj
{
	t_shape		shape;
	t_material	material;
	t_vec		axis;
	t_vec		translation;
	t_mat		rmat;
}	t_obj;

// increment to reallocate for touches array
// minimizing nbr of allocations
# define INTERSECTION_BUFFER_STEP 8

typedef struct s_touch
{
	double	t;
	t_obj	*obj;
}	t_touch;

typedef struct s_touches
{
	t_touch	*hit;
	size_t	size;
	t_touch	*is;
}	t_touches;

typedef struct s_hit
{
	t_touch	i;
	t_vec	point;
	t_vec	normal;
	t_vec	eyev;
	int		is_inside;
}	t_hit;

// default cam origin
typedef struct s_cam
{
	double	scale;
	double	hsize;
	double	vsize;
	double	pixel_size;
	double	half_width;
	double	half_height;
	t_vec	origin;
	t_vec	axis;
	t_vec	left;
	t_vec	up;
	double	fov;
	t_mat	rmat;
}	t_cam;

typedef struct s_img
{
	void	*img;
	char	*addr;
	void	*mlx;
	void	*win;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef volatile struct s_world
{
	t_vec		ray_origin;
	t_list		*objs;
	t_vec		amb;
	t_spotlight	light;
	t_img		*img;
	t_cam		cam;
	t_scenehe	*scene;
	t_vec		dir_rot;
	t_vec		dir_move;
	t_obj		*selected_obj;
	int			selected_light;
}	t_world;

typedef struct s_scene
{
	t_cam	*cam;
	t_world	*world;
	t_vec	tmp;
	void	*mlx_ptr;
	void	*mlx_win;
	t_img	*img;
}	t_scene;

t_img		*my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* ************************************************************************** */
// light.c
t_vec		vec_reflect(t_vec in, t_vec n);
t_phong		lighting(t_material mat, t_spotlight light, t_hit hit, int shadow);
t_spotlight	*light_translate(t_spotlight *light, t_vec dir, double shift);
// interface:
t_spotlight	light_init(t_light l);
/* ************************************************************************** */
// ray.c
t_vec		ray_position(t_ray ray, double t);
t_roots		quadratic_roots(double a, double b, double c);
t_touches	*ray_world_hits(t_touches *is, t_ray ray, t_world *world);

t_roots		ray_sphere_intersect(t_ray ray, t_obj *obj);
t_roots		ray_cylinder_intersect(t_ray ray, t_obj *obj);
t_roots		ray_plane_intersect(t_ray ray);
t_roots		ray_obj_intersect(t_ray ray, t_obj *obj);

/* ************************************************************************** */
// shape.c
t_shape		shape_sphere_create(void);
t_shape		shape_cylinder_create(void);
t_shape		shape_cone_create(void);
t_shape		shape_plane_create(void);
t_shape		*shape_scale(t_shape *shape, double scale);

/* ************************************************************************** */
// obj.c
// interface:
t_obj		*obj_translate(t_obj *obj, t_vec dir, double shift);
t_obj		*obj_rotate(t_obj *obj, t_vec euler);
t_obj		*obj_scale(t_obj *obj, double scale);
t_obj		*obj_select(t_world *world, int x, int y);
t_obj		*obj_new_height(t_obj *obj, double height);

/* ************************************************************************** */
// obj_create.c
// interface:
t_obj		*obj_sphere_create(t_sphere s);
t_obj		*obj_cylinder_create(t_cylinder c);
t_obj		*obj_plane_create(t_plane p);
t_vec		normal_at(t_vec p, t_obj obj);

/* ************************************************************************** */
// world.c
// interface:
t_world		*world_obj_add(t_world *world, t_obj *obj);
void		world_destroy(t_world *world);
t_world		*world_init(t_world *world);

/* ************************************************************************** */
// touches.c
t_touches	*touches_roots_add(t_touches *is, t_roots xs, t_obj *obj);
t_touches	*touches_init(t_touches *is);

/* ************************************************************************** */
// hit.c
t_hit		hit(t_touch i, t_ray ray);
t_vec		shade_hit(t_world *world, t_hit hit);
t_vec		color_at(t_world *world, t_ray ray);

/* ************************************************************************** */
// cam.c
t_ray		ray_for_pixel(t_cam *cam, int x, int y);
t_img		*render(t_img *img, t_cam *cam, t_world *world);
t_vec		color_blend(t_vec c1, t_vec c2);

/* ************************************************************************** */
// cam_interface.c
t_cam		cam_init(t_scenehe *scene);
t_cam		*cam_rescale(t_cam *cam, double new_scale);
t_cam		*cam_coord_new(t_cam *cam, t_vec coord);
t_cam		*cam_translate(t_cam *cam, t_vec dir, double shift);
t_cam		*cam_rotate(t_cam *cam, t_vec euler);

//render scene
void		render_scene(t_scenehe *scene, t_world *world);

t_img		img_init(t_data *data);
void		init_scene(t_scenehe *scene);

t_img		img_init(t_data *data);
void		init_scene(t_scenehe *scene);
void		handle_scaling(int keycode, t_obj *obj);
void		handle_movement(int keycode, t_world *world, t_cam cam);

#endif
