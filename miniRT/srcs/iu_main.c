#include "iu_scene.h"

int main(int argc, char **argv) 
{
    static t_world	world;
    t_data data = {0};
    t_scenehe scenehe = {0};

    if (argc != 2)
        ft_error("Usage: ./miniRT <scene_description_file.rt>", &data, EXIT_FAILURE);
    // Calculate the length of the filename
    size_t filename_len = ft_strlen(argv[1]);
    size_t extension_len = ft_strlen(".rt");
    if (filename_len < extension_len || !ft_strnstr(argv[1] + filename_len - extension_len, ".rt", extension_len)) {
        ft_error("Usage: ./miniRT <scene_description_file.rt>", &data, EXIT_FAILURE);
    }
    //ft_checkfile(argv[1], &data);
    printf("Parsing scene\n");
    parse_scene(argv[1], &scenehe);
    printf("Opening window\n");
    open_window(&data);
    printf("Initializing world\n");
	world_init(&world);

    // Render the scene using the parsed data
    printf("Rendering scene\n");
    render_scene(&data, &scenehe, &world);

    ft_error(NULL, &data, EXIT_SUCCESS);
}

/* int main(void)
{
    const char *color_str = "255,128,64";
    t_color color;
    t_scene scene;
    parse_color(&color_str, &color, &scene);
    printf("Parsed color: R=%d, G=%d, B=%d\n", color.r, color.g, color.b);
} */