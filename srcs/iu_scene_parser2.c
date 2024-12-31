/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_parser2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:31:47 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/12 11:01:43 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_amb(const char *line, t_scenehe *scene)
{
	const int	fail = EXIT_FAILURE;

	line++;
	skip_spaces(&line);
	scene->amb.ratio = parse_float(&line, 1, 0.0);
	if (scene->amb.ratio < 0.0 || scene->amb.ratio > 1.0)
		ft_error("Ambient: Light ratio out of range [0.0, 1.0]", scene, fail);
	skip_spaces(&line);
	parse_color(&line, &scene->amb.color, scene);
}

void	parse_cam(const char *line, t_scenehe *scene)
{
	const int	fail = EXIT_FAILURE;

	line++;
	skip_spaces(&line);
	scene->cam.x = parse_float(&line, 1, 0.0);
	line++;
	scene->cam.y = parse_float(&line, 1, 0.0);
	line++;
	scene->cam.z = parse_float(&line, 1, 0.0);
	skip_spaces(&line);
	scene->cam.dx = parse_float(&line, 1, 0.0);
	line++;
	scene->cam.dy = parse_float(&line, 1, 0.0);
	line++;
	scene->cam.dz = parse_float(&line, 1, 0.0);
	if (scene->cam.dx < -1.0 || scene->cam.dx > 1.0 \
		|| scene->cam.dy < -1.0 || scene->cam.dy > 1.0 \
		|| scene->cam.dz < -1.0 || scene->cam.dz > 1.0)
		ft_error("Camera: Orientation out of range [-1.0, 1.0]", scene, fail);
	skip_spaces(&line);
	scene->cam.fov = parse_float(&line, 1, 0.0);
	if (scene->cam.fov < 0 || scene->cam.fov > 180)
		ft_error("Camera: FOV out of range [0, 180[", scene, fail);
}

void	parse_light(const char *line, t_scenehe *scene)
{
	const int	fail = EXIT_FAILURE;

	line++;
	skip_spaces(&line);
	scene->light.x = parse_float(&line, 1, 0.0);
	line++;
	scene->light.y = parse_float(&line, 1, 0.0);
	line++;
	scene->light.z = parse_float(&line, 1, 0.0);
	skip_spaces(&line);
	scene->light.brightness = parse_float(&line, 1, 0.0);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		ft_error("Light: Brightness out of range [0.0, 1.0]", scene, fail);
	skip_spaces(&line);
	parse_color(&line, &scene->light.color, scene);
}

void	parse_sphere(const char *line, t_scenehe *scene)
{
	t_sphere	sphere;

	line += 2;
	skip_spaces(&line);
	sphere.x = parse_float(&line, 1, 0.0);
	line++;
	sphere.y = parse_float(&line, 1, 0.0);
	line++;
	sphere.z = parse_float(&line, 1, 0.0);
	skip_spaces(&line);
	sphere.diameter = parse_float(&line, 1, 0.0);
	if (sphere.diameter <= 0.0)
		ft_error("Sphere: Diameter must be positive", scene, EXIT_FAILURE);
	skip_spaces(&line);
	parse_color(&line, &sphere.color, scene);
	scene->spheres = ft_realloc(scene->spheres, sizeof(t_sphere), \
			(scene->sphere_count + 1));
	scene->spheres[scene->sphere_count++] = sphere;
}

void	parse_plane(const char *line, t_scenehe *scene)
{
	t_plane		plane;
	const int	fail = EXIT_FAILURE;

	line += 2;
	skip_spaces(&line);
	plane.x = parse_float(&line, 1, 0.0);
	line++;
	plane.y = parse_float(&line, 1, 0.0);
	line++;
	plane.z = parse_float(&line, 1, 0.0);
	skip_spaces(&line);
	plane.dx = parse_float(&line, 1, 0.0);
	line++;
	plane.dy = parse_float(&line, 1, 0.0);
	line++;
	plane.dz = parse_float(&line, 1, 0.0);
	if (plane.dx < -1.0 || plane.dx > 1.0 || plane.dy < -1.0
		|| plane.dy > 1.0 || plane.dz < -1.0
		|| plane.dz > 1.0)
		ft_error("Plane: Orientation out of range [-1.0, 1.0]", scene, fail);
	skip_spaces(&line);
	parse_color(&line, &plane.color, scene);
	scene->planes = ft_realloc(scene->planes, sizeof(t_plane), \
			(scene->plane_count + 1));
	scene->planes[scene->plane_count++] = plane;
}
