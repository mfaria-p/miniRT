#include "iu_scene.h"

int main(int argc, char **argv) 
{
    t_data data = {0};
    t_scene scene = {0};

    if (argc != 2)
        ft_error("Usage: ./miniRT <scene_description_file.rt>", &data, EXIT_FAILURE);
    // Calculate the length of the filename
    size_t filename_len = ft_strlen(argv[1]);
    size_t extension_len = ft_strlen(".rt");
    if (filename_len < extension_len || !ft_strnstr(argv[1] + filename_len - extension_len, ".rt", extension_len)) {
        ft_error("Usage: ./miniRT <scene_description_file.rt>", &data, EXIT_FAILURE);
    }
    //ft_checkfile(argv[1], &data);
    parse_scene(argv[1], &scene);
    open_window(&data);
    ft_error(NULL, &data, EXIT_SUCCESS);

    // Render the scene using the parsed data
    //render_scene(&data, &scene);
}

/* int main(void)
{
    const char *color_str = "255,128,64";
    t_color color;
    t_scene scene;
    parse_color(&color_str, &color, &scene);
    printf("Parsed color: R=%d, G=%d, B=%d\n", color.r, color.g, color.b);
} */