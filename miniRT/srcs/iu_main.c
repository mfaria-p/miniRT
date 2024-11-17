#include "iu_scene.h"

void init_scene(t_scenehe *scene) {
    scene->data.mlx_ptr = NULL;
    scene->data.win_ptr = NULL;
    scene->data.img_ptr = NULL;
    scene->data.img_data = NULL;
    scene->line = NULL;
    scene->params = NULL;
    scene->data.bpp = 0;
    scene->data.size_line = 0;
    scene->data.endian = 0;
    scene->data.fd = 0;
    scene->ambient.ratio = 0.0;
    scene->ambient.color = (t_color){0, 0, 0};
    scene->camera = (t_camerahe){0};
    scene->light = (t_light){0};
    scene->spheres = NULL;
    scene->sphere_count = 0;
    scene->planes = NULL;
    scene->plane_count = 0;
    scene->cylinders = NULL;
    scene->cylinder_count = 0;
    scene->camera_count = 0;
    scene->light_count = 0;
    scene->ambient_count = 0;
}

int main(int argc, char **argv) 
{
    static t_world	world;
    t_scenehe scenehe;

    init_scene(&scenehe);

    if (argc != 2)
        ft_error("Usage: ./miniRT <scene_description_file.rt>", &scenehe, EXIT_FAILURE);
    // Calculate the length of the filename
    size_t filename_len = ft_strlen(argv[1]);
    size_t extension_len = ft_strlen(".rt");
    if (filename_len < extension_len || !ft_strnstr(argv[1] + filename_len - extension_len, ".rt", extension_len)) {
        ft_error("Usage: ./miniRT <scene_description_file.rt>", &scenehe, EXIT_FAILURE);
    }
    //ft_checkfile(argv[1], &data);
    printf("Parsing scene\n");
    parse_scene(argv[1], &scenehe);
    printf("Opening window\n");
    open_window(&scenehe);
    printf("Initializing world\n");
	world_init(&world);

    // Render the scene using the parsed data
    printf("Rendering scene\n");
    render_scene(&scenehe, &world);

    ft_error(NULL, &scenehe, EXIT_SUCCESS);
}

/* int main(void)
{
    const char *color_str = "255,128,64";
    t_color color;
    t_scene scene;
    parse_color(&color_str, &color, &scene);
    printf("Parsed color: R=%d, G=%d, B=%d\n", color.r, color.g, color.b);
} */