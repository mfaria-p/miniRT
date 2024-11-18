#include "iu_scene.h"

void parse_ambient(const char *line, t_scenehe *scene) {
    line++; // skip 'A'
    skip_spaces(&line);
    scene->ambient.ratio = parse_float(&line);
    if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0) 
    ft_error("Ambient lighting ratio out of range [0.0, 1.0]", scene, EXIT_FAILURE);
    skip_spaces(&line);
    parse_color(&line, &scene->ambient.color, scene);
}

void parse_camera(const char *line, t_scenehe *scene) {
    printf("Parsing camera\n");
    line++; // skip 'C'
    skip_spaces(&line);
    scene->camera.x = parse_float(&line);
    printf("Parsed camera x: %f\n", scene->camera.x);
    line++; // skip comma
    scene->camera.y = parse_float(&line);
    printf("Parsed camera y: %f\n", scene->camera.y);
    line++; // skip comma
    scene->camera.z = parse_float(&line);
    printf("Parsed camera z: %f\n", scene->camera.z);

    skip_spaces(&line);
    scene->camera.orient_x = parse_float(&line);
    printf("Parsed camera orient_x: %f\n", scene->camera.orient_x);
    line++; // skip comma
    scene->camera.orient_y = parse_float(&line);
    printf("Parsed camera orient_y: %f\n", scene->camera.orient_y);
    line++; // skip comma
    scene->camera.orient_z = parse_float(&line);
    printf("Parsed camera orient_z: %f\n", scene->camera.orient_z);

    if (scene->camera.orient_x < -1.0 || scene->camera.orient_x > 1.0 ||
        scene->camera.orient_y < -1.0 || scene->camera.orient_y > 1.0 ||
        scene->camera.orient_z < -1.0 || scene->camera.orient_z > 1.0)
        ft_error("Camera orientation values out of range [-1.0, 1.0]", scene, EXIT_FAILURE);

    skip_spaces(&line);
    scene->camera.fov = parse_float(&line);
    printf("Parsed camera fov: %f\n", scene->camera.fov);
    if (scene->camera.fov < 0 || scene->camera.fov > 180) 
        ft_error("Camera FOV out of range [0, 180]", scene, EXIT_FAILURE);
}

void parse_light(const char *line, t_scenehe *scene) {
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
        ft_error("Light brightness out of range [0.0, 1.0]", scene, EXIT_FAILURE);

    skip_spaces(&line);
    parse_color(&line, &scene->light.color, scene);
}

void parse_sphere(const char *line, t_scenehe *scene) {
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
	printf("%f\n",sphere.diameter);
    if (sphere.diameter <= 0.0) 
        ft_error("Sphere diameter must be positive", scene, EXIT_FAILURE);

    skip_spaces(&line);
    parse_color(&line, &sphere.color, scene);

    scene->spheres = ft_realloc(scene->spheres, sizeof(t_sphere) * (scene->sphere_count + 1));
    scene->spheres[scene->sphere_count++] = sphere;
}

void parse_plane(const char *line, t_scenehe *scene) {
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
        ft_error("Plane orientation values out of range [-1.0, 1.0]", scene, EXIT_FAILURE);

    skip_spaces(&line);
    parse_color(&line, &plane.color, scene);

    scene->planes = ft_realloc(scene->planes, sizeof(t_plane) * (scene->plane_count + 1));
    scene->planes[scene->plane_count++] = plane;
}

void parse_cylinder(const char *line, t_scenehe *scene) {
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
        ft_error("Cylinder orientation values out of range [-1.0, 1.0]", scene, EXIT_FAILURE);

    skip_spaces(&line);
    cylinder.diameter = parse_float(&line);
    if (cylinder.diameter <= 0.0)
        ft_error("Cylinder diameter must be positive", scene, EXIT_FAILURE);

    skip_spaces(&line);
    cylinder.height = parse_float(&line);
    if (cylinder.height <= 0.0) 
        ft_error("Cylinder height must be positive", scene, EXIT_FAILURE);

    skip_spaces(&line);
    parse_color(&line, &cylinder.color, scene);

    scene->cylinders = ft_realloc(scene->cylinders, sizeof(t_cylinder) * (scene->cylinder_count + 1));
    scene->cylinders[scene->cylinder_count++] = cylinder;
}

void process_line(char *line, t_scenehe *scene) {
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        len--; // Exclude the newline character
    }

    // Allocate a new buffer and copy the content up to the newline character
    char *clean_line = (char *)malloc(len + 1);
    if (!clean_line) {
        ft_error("Memory allocation failed", scene, EXIT_FAILURE);
    }
    ft_memcpy(clean_line, scene->line, len);
    if (scene->line)
    {
        free(scene->line); // Free the original buffer after copying
        scene->line = NULL; // Set to NULL after freeing
    }
    clean_line[len] = '\0'; // Null-terminate the new buffer
    scene->line = clean_line;

    // Process the clean line
    if (clean_line[0] == 'A') {
        check_ambient(clean_line, scene);
    } else if (clean_line[0] == 'C') {
        check_camera(clean_line, scene);
    } else if (clean_line[0] == 'L') {
        check_light(clean_line, scene);
    } else if (ft_strncmp(clean_line, "sp", 2) == 0) {
        check_sphere(clean_line, scene);
    } else if (ft_strncmp(clean_line, "pl", 2) == 0) {
        check_plane(clean_line, scene);
    } else if (ft_strncmp(clean_line, "cy", 2) == 0) {
        check_cylinder(clean_line, scene);
    } else {
        ft_error("Invalid element", scene, EXIT_FAILURE);
    }
    if(scene->line)
    {
        free(scene->line); // Free the new buffer after processing
        scene->line = NULL; // Set to NULL after freeing
    }
}

void parse_scene(const char *filename, t_scenehe *scene) {
    scene->data.fd = open(filename, O_RDONLY);
    if (scene->data.fd < 0) {
        ft_error("Failed to open file", scene, EXIT_FAILURE);
    }

    scene->ambient_count=0;
    scene->light_count=0;
    scene->camera_count=0;
    while ((scene->line = get_next_line(scene->data.fd)) != NULL) {
        if (scene->line[0] == '\n') {
            free(scene->line);
            scene->line = NULL; // Set to NULL after freeing
            continue;
        }
        process_line(scene->line, scene);
        if (scene->line)
        {
            free(scene->line);
            scene->line = NULL; // Set to NULL after freeing
        }
    }
    close(scene->data.fd);  // Close the file descriptor after reading all lines
    is_invalid_file(scene);
}

void check_ambient(const char *line, t_scenehe *scene) 
{
	char		**params;

    scene->ambient_count++;
    if (scene->ambient_count > 1)
    {
        ft_error("You cannot declare more than one Ambient", scene, EXIT_FAILURE);
    }
	params = ft_split(line, ' ');
    if (array_length(params) != 3)
    {
        free_array(params);
		ft_error("Invalid number of parameters for ambient element", scene, EXIT_FAILURE);
    }
    if (!is_float(params[1])) {
        free_array(params);
        ft_error("Ambient lighting ratio must be a float number", scene, EXIT_FAILURE);
    }
    check_colors(&params, scene, 2);
    free_array(params);
    parse_ambient(line, scene);
}

void check_camera(const char *line, t_scenehe *scene) 
{
	char		**params;

    scene->camera_count++;
    if (scene->camera_count > 1)
    {
        ft_error("You cannot declare more than one Camera", scene, EXIT_FAILURE);
    }
	params = ft_split(line, ' ');
    if (array_length(params) != 4)
    {
        free_array(params);
		ft_error("Invalid number of parameters for camera element", scene, EXIT_FAILURE);
    }
    check_vector(&params, scene, 1);
    check_vector(&params, scene, 2);
    if (!is_float(params[3])) {
        free_array(params);
        ft_error("Camera FOV must be a float number", scene, EXIT_FAILURE);
    }
    free_array(params);
    parse_camera(line, scene);
}

void check_light(const char *line, t_scenehe *scene) 
{
	char		**params;

    scene->light_count++;
    if (scene->light_count > 1)
    {
        ft_error("You cannot declare more than one Light", scene, EXIT_FAILURE);
    }
	params = ft_split(line, ' ');
    if (array_length(params) != 4)
    {
        free_array(params);
		ft_error("Invalid number of parameters for Light element", scene, EXIT_FAILURE);
    }
    check_vector(&params, scene, 1);
    if (!is_float(params[2])) {
        free_array(params);
        ft_error("Light brightness ratio must be a float number", scene, EXIT_FAILURE);
    }
    check_colors(&params, scene, 3);
    free_array(params);
    parse_light(line, scene);
}

void check_sphere(const char *line, t_scenehe *scene) 
{
	char		**params;

    params = ft_split(line, ' ');
    if (array_length(params) != 4)
    {
        free_array(params);
		ft_error("Invalid number of parameters for sphere element", scene, EXIT_FAILURE);
    }
    check_vector(&params, scene, 1);
    if (!is_float(params[2])) {
        free_array(params);
        ft_error("Sphere Diameter must be a float number", scene, EXIT_FAILURE);
    }
    check_colors(&params, scene, 3);
    free_array(params);
    parse_sphere(line, scene);
}	

void check_plane(const char *line, t_scenehe *scene) 
{
	char		**params;

    params = ft_split(line, ' ');
    if (array_length(params) != 4)
    {
        free_array(params);
		ft_error("Invalid number of parameters for plane element", scene, EXIT_FAILURE);
    }
    check_vector(&params, scene, 1);
    check_vector(&params, scene, 2);
    check_colors(&params, scene, 3);
    free_array(params);
    parse_plane(line, scene);
}

void check_cylinder(const char *line, t_scenehe *scene) 
{
	char		**params;

    params = ft_split(line, ' ');
    if (array_length(params) != 6)
    {
        free_array(params);
		ft_error("Invalid number of parameters for cylinder element", scene, EXIT_FAILURE);
    }
    check_vector(&params, scene, 1);
    check_vector(&params, scene, 2);
    if (!is_float(params[3])) {
        free_array(params);
        ft_error("Cylinder Diameter must be a float number", scene, EXIT_FAILURE);
    }
    if (!is_float(params[4])) {
        free_array(params);
        ft_error("Cylinder Height must be a float number", scene, EXIT_FAILURE);
    }
    check_colors(&params, scene, 5);
    free_array(params);
    parse_cylinder(line, scene);
}

void	check_vector(char ***str, t_scenehe *scene, int j)
{
	int		i;
	char	**nbrs;

	i = 0;
	nbrs = ft_split((*str)[j], ',');
	if (!nbrs) {
        free_array(*str);
        *str = NULL;
        ft_error("Memory allocation failed for nbrs", scene, EXIT_FAILURE);
    }
    while (nbrs[i]) {
        if (!is_float(nbrs[i])) {
            free_array(*str);
            *str = NULL;
            free_array(nbrs);
            nbrs = NULL;
            ft_error("All parameters must be numbers", scene, EXIT_FAILURE);
        }
        i++;
    }
	if (array_length(nbrs) != 3)
    {
        free_array(*str);
        *str = NULL;
        free_array(nbrs);
        nbrs = NULL;
		ft_error("You must input x, y and z axis.", scene, EXIT_FAILURE);
    }
	free_array(nbrs);
    nbrs = NULL;
}

void	check_colors(char ***str, t_scenehe *scene, int j)
{
    int		i;
	char	**nbrs;

	i = -1;
	nbrs = ft_split((*str)[j], ',');
    while (nbrs && nbrs[++i]) {
        if (is_int(nbrs[i]) == 0) {
            free_array(*str);
            free_array(nbrs);
            ft_error("RGB colors must be constituted of integers numbers only", scene, EXIT_FAILURE);
        }
    }
	if (array_length(nbrs) != 3)
    {
        free_array(*str);
        free_array(nbrs);
		ft_error("You must input three integers numbers for RGB colors.", scene, EXIT_FAILURE);
    }
	free_array(nbrs);
}
