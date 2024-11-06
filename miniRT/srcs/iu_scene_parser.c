#include "iu_scene.h"

static void parse_ambient(const char *line, t_scene *scene) {
    line++; // skip 'A'
    skip_spaces(&line);
    scene->ambient.ratio = parse_float(&line);
    if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0) 
    ft_error("Ambient lighting ratio out of range [0.0, 1.0]", scene->data, EXIT_FAILURE);
    skip_spaces(&line);
    parse_color(&line, &scene->ambient.color);
}

static void parse_camera(const char *line, t_scene *scene) {
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
        ft_error("Camera orientation values out of range [-1.0, 1.0]", scene->data, EXIT_FAILURE);

    skip_spaces(&line);
    scene->camera.fov = parse_int(&line);
    if (scene->camera.fov < 0 || scene->camera.fov > 180) 
        ft_error("Camera FOV out of range [0, 180]", scene->data, EXIT_FAILURE);
}

static void parse_light(const char *line, t_scene *scene) {
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
        ft_error("Light brightness out of range [0.0, 1.0]", scene->data, EXIT_FAILURE);

    skip_spaces(&line);
    parse_color(&line, &scene->light.color);
}

static void parse_sphere(const char *line, t_scene *scene) {
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
    if (sphere.diameter <= 0.0) parse_error("Sphere diameter must be positive");

    skip_spaces(&line);
    parse_color(&line, &sphere.color);

    scene->spheres = realloc(scene->spheres, sizeof(t_sphere) * (scene->sphere_count + 1));
    scene->spheres[scene->sphere_count++] = sphere;
}