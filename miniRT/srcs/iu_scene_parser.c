#include "iu_scene.h"

void parse_ambient(const char *line, t_scene *scene) {
    line++; // skip 'A'
    skip_spaces(&line);
    scene->ambient.ratio = parse_float(&line);
    if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0) 
    ft_error("Ambient lighting ratio out of range [0.0, 1.0]", &scene->data, EXIT_FAILURE);
    skip_spaces(&line);
    printf("line: %s\n", line);
    parse_color(&line, &scene->ambient.color, scene);
}

void parse_camera(const char *line, t_scene *scene) {
    line++; // skip 'C'
    skip_spaces(&line);
    scene->camera.x = parse_float(&line);
    line++; // skip comma
    scene->camera.y = parse_float(&line);
    line++; // skip comma
    scene->camera.z = parse_float(&line);

    skip_spaces(&line);
    scene->camera.orient_x = parse_float(&line);
    line++; // skip comma
    scene->camera.orient_y = parse_float(&line);
    line++; // skip comma
    scene->camera.orient_z = parse_float(&line);

    if (scene->camera.orient_x < -1.0 || scene->camera.orient_x > 1.0 ||
        scene->camera.orient_y < -1.0 || scene->camera.orient_y > 1.0 ||
        scene->camera.orient_z < -1.0 || scene->camera.orient_z > 1.0)
        ft_error("Camera orientation values out of range [-1.0, 1.0]", &scene->data, EXIT_FAILURE);

    skip_spaces(&line);
    scene->camera.fov = parse_int(&line);
    if (scene->camera.fov < 0 || scene->camera.fov > 180) 
        ft_error("Camera FOV out of range [0, 180]", &scene->data, EXIT_FAILURE);
}

void parse_light(const char *line, t_scene *scene) {
    line++; // skip 'L'
    skip_spaces(&line);
    scene->light.x = parse_float(&line);
    line++; // skip comma
    scene->light.y = parse_float(&line);
    line++; // skip comma
    scene->light.z = parse_float(&line);

    skip_spaces(&line);
    scene->light.brightness = parse_float(&line);
    if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0) 
        ft_error("Light brightness out of range [0.0, 1.0]", &scene->data, EXIT_FAILURE);

    skip_spaces(&line);
    printf("line: %s\n", line);
    parse_color(&line, &scene->light.color, scene);
}

void parse_sphere(const char *line, t_scene *scene) {
    t_sphere sphere;
    line += 2; // skip 'sp'
    skip_spaces(&line);
    sphere.x = parse_float(&line);
    line++; // skip comma
    sphere.y = parse_float(&line);
    line++; // skip comma
    sphere.z = parse_float(&line);

    skip_spaces(&line);
    sphere.diameter = parse_float(&line);
    if (sphere.diameter <= 0.0) ft_error("Sphere diameter must be positive", &scene->data, EXIT_FAILURE);

    skip_spaces(&line);
    printf("line: %s\n", line);
    parse_color(&line, &sphere.color, scene);

    scene->spheres = ft_realloc(scene->spheres, sizeof(t_sphere) * (scene->sphere_count + 1));
    scene->spheres[scene->sphere_count++] = sphere;
}

void parse_plane(const char *line, t_scene *scene) {
    t_plane plane;
    line += 2; // skip 'pl'
    skip_spaces(&line);
    plane.x = parse_float(&line);
    line++; // skip comma
    plane.y = parse_float(&line);
    line++; // skip comma
    plane.z = parse_float(&line);

    skip_spaces(&line);
    plane.orient_x = parse_float(&line);
    line++; // skip comma
    plane.orient_y = parse_float(&line);
    line++; // skip comma
    plane.orient_z = parse_float(&line);

    if (plane.orient_x < -1.0 || plane.orient_x > 1.0 ||
        plane.orient_y < -1.0 || plane.orient_y > 1.0 ||
        plane.orient_z < -1.0 || plane.orient_z > 1.0)
        ft_error("Plane orientation values out of range [-1.0, 1.0]", &scene->data, EXIT_FAILURE);

    skip_spaces(&line);
    printf("line: %s\n", line);
    parse_color(&line, &plane.color, scene);

    scene->planes = ft_realloc(scene->planes, sizeof(t_plane) * (scene->plane_count + 1));
    scene->planes[scene->plane_count++] = plane;
}

void parse_cylinder(const char *line, t_scene *scene) {
    t_cylinder cylinder;
    line += 2; // skip 'cy'
    skip_spaces(&line);
    cylinder.x = parse_float(&line);
    line++; // skip comma
    cylinder.y = parse_float(&line);
    line++; // skip comma
    cylinder.z = parse_float(&line);

    skip_spaces(&line);
    cylinder.orient_x = parse_float(&line);
    line++; // skip comma
    cylinder.orient_y = parse_float(&line);
    line++; // skip comma
    cylinder.orient_z = parse_float(&line);

    if (cylinder.orient_x < -1.0 || cylinder.orient_x > 1.0 ||
        cylinder.orient_y < -1.0 || cylinder.orient_y > 1.0 ||
        cylinder.orient_z < -1.0 || cylinder.orient_z > 1.0)
        ft_error("Cylinder orientation values out of range [-1.0, 1.0]", &scene->data, EXIT_FAILURE);

    skip_spaces(&line);
    cylinder.diameter = parse_float(&line);
    if (cylinder.diameter <= 0.0)
        ft_error("Cylinder diameter must be positive", &scene->data, EXIT_FAILURE);

    skip_spaces(&line);
    cylinder.height = parse_float(&line);
    if (cylinder.height <= 0.0) 
        ft_error("Cylinder height must be positive", &scene->data, EXIT_FAILURE);

    skip_spaces(&line);
    printf("line: %s\n", line);
    parse_color(&line, &cylinder.color, scene);

    scene->cylinders = ft_realloc(scene->cylinders, sizeof(t_cylinder) * (scene->cylinder_count + 1));
    scene->cylinders[scene->cylinder_count++] = cylinder;
}

void parse_scene(const char *filename, t_scene *scene) {
    int fd = open(filename, O_RDONLY);
    char *line;

    // Use get_next_line to read each line
    while ((line = get_next_line(fd)) != NULL) {
        if (line[0] == 'A') {
            parse_ambient(line, scene);
        } else if (line[0] == 'C') {
            parse_camera(line, scene);
        } else if (line[0] == 'L') {
            parse_light(line, scene);
        } else if (strncmp(line, "sp", 2) == 0) {
            parse_sphere(line, scene);
        } else if (strncmp(line, "pl", 2) == 0) {
            parse_plane(line, scene);
        } else if (strncmp(line, "cy", 2) == 0) {
            parse_cylinder(line, scene);
        }
        free(line);  // Free each line after processing
    }
    close(fd);  // Close the file descriptor after reading all lines
}