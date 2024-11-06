#include "iu_scene.h"

int main(int argc, char **argv) {
    t_data data;

    if (argc != 2 || !strstr(argv[1], ".rt")) 
    ft_error( "Usage: ./miniRT <scene_description_file.rt>", data, EXIT_FAILURE);
    ft_checkfile(argv[1]);
    open_window(&data);

}