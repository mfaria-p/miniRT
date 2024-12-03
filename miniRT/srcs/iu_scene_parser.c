/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:12:33 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 17:49:20 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	printf("%f\n", sphere.diameter);
	if (sphere.diameter <= 0.0)
		ft_error("Sphere diameter must be positive", scene, EXIT_FAILURE);
	skip_spaces(&line);
	parse_color(&line, &sphere.color, scene);
	scene->spheres = ft_realloc(scene->spheres, sizeof(t_sphere)
			* (scene->sphere_count + 1));
	scene->spheres[scene->sphere_count++] = sphere;
}

void	parse_plane(const char *line, t_scenehe *scene)
{
	t_plane	plane;

	line += 2;
	skip_spaces(&line);
	plane.x = parse_float(&line, 1, 0.0);
	line++;
	plane.y = parse_float(&line, 1, 0.0);
	line++;
	plane.z = parse_float(&line, 1, 0.0);
	skip_spaces(&line);
	plane.orient_x = parse_float(&line, 1, 0.0);
	line++;
	plane.orient_y = parse_float(&line, 1, 0.0);
	line++;
	plane.orient_z = parse_float(&line, 1, 0.0);
	if (plane.orient_x < -1.0 || plane.orient_x > 1.0 || plane.orient_y < -1.0
		|| plane.orient_y > 1.0 || plane.orient_z < -1.0
		|| plane.orient_z > 1.0)
		ft_error("Plane orientation values out of range [-1.0, 1.0]", scene,
			EXIT_FAILURE);
	skip_spaces(&line);
	parse_color(&line, &plane.color, scene);
	scene->planes = ft_realloc(scene->planes, sizeof(t_plane)
			* (scene->plane_count + 1));
	scene->planes[scene->plane_count++] = plane;
}

void	parse_cylinder(const char *line, t_scenehe *scene)
{
	t_cylinder	cylinder;

	line += 2;
	skip_spaces(&line);
	cylinder.x = parse_float(&line, 1, 0.0);
	line++;
	cylinder.y = parse_float(&line, 1, 0.0);
	line++;
	cylinder.z = parse_float(&line, 1, 0.0);
	skip_spaces(&line);
	cylinder.orient_x = parse_float(&line, 1, 0.0);
	line++;
	cylinder.orient_y = parse_float(&line, 1, 0.0);
	line++;
	cylinder.orient_z = parse_float(&line, 1, 0.0);
	if (cylinder.orient_x < -1.0 || cylinder.orient_x > 1.0
		|| cylinder.orient_y < -1.0 || cylinder.orient_y > 1.0
		|| cylinder.orient_z < -1.0 || cylinder.orient_z > 1.0)
		ft_error("Cylinder orientation values out of range [-1.0, 1.0]", scene,
			EXIT_FAILURE);
	skip_spaces(&line);
	cylinder.diameter = parse_float(&line, 1, 0.0);
	if (cylinder.diameter <= 0.0)
		ft_error("Cylinder diameter must be positive", scene, EXIT_FAILURE);
	skip_spaces(&line);
	cylinder.height = parse_float(&line, 1, 0.0);
	if (cylinder.height <= 0.0)
		ft_error("Cylinder height must be positive", scene, EXIT_FAILURE);
	skip_spaces(&line);
	parse_color(&line, &cylinder.color, scene);
	scene->cylinders = ft_realloc(scene->cylinders, sizeof(t_cylinder)
			* (scene->cylinder_count + 1));
	scene->cylinders[scene->cylinder_count++] = cylinder;
}

void	process_line(char *line, t_scenehe *scene)
{
	size_t	len;
	char	*clean_line;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	clean_line = (char *)malloc(len + 1);
	if (!clean_line)
		ft_error("Memory allocation failed", scene, EXIT_FAILURE);
	ft_memcpy(clean_line, scene->line, len);
	if (scene->line)
	{
		free(scene->line);
		scene->line = NULL;
	}
	clean_line[len] = '\0';
	scene->line = clean_line;
	if (clean_line[0] == 'A')
		check_ambient(clean_line, scene);
	else if (clean_line[0] == 'C')
		check_camera(clean_line, scene);
	else if (clean_line[0] == 'L')
		check_light(clean_line, scene);
	else if (ft_strncmp(clean_line, "sp", 2) == 0)
		check_sphere(clean_line, scene);
	else if (ft_strncmp(clean_line, "pl", 2) == 0)
		check_plane(clean_line, scene);
	else if (ft_strncmp(clean_line, "cy", 2) == 0)
		check_cylinder(clean_line, scene);
	else
		ft_error("Invalid element", scene, EXIT_FAILURE);
	if (scene->line)
	{
		free(scene->line);
		scene->line = NULL;
	}
}

void	parse_scene(const char *filename, t_scenehe *scene)
{
	scene->data.fd = open(filename, O_RDONLY);
	if (scene->data.fd < 0)
		ft_error("Failed to open file", scene, EXIT_FAILURE);
	while (1)
	{
		scene->line = get_next_line(scene->data.fd);
		if (scene->line == NULL)
			break ;
		if (scene->line[0] == '\n')
		{
			free(scene->line);
			scene->line = NULL;
			continue ;
		}
		process_line(scene->line, scene);
		if (scene->line)
		{
			free(scene->line);
			scene->line = NULL;
		}
	}
	close(scene->data.fd);
	is_invalid_file(scene);
}
