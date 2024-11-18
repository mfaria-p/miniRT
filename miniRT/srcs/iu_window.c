#include "iu_scene.h"

void open_window(t_scenehe *scene) {
    scene->data.mlx_ptr = mlx_init();
    if (!scene->data.mlx_ptr)
        ft_error("Initializing MiniLibX", scene, EXIT_FAILURE);
    scene->data.win_ptr = mlx_new_window(scene->data.mlx_ptr, CANVAS_PIXEL, CANVAS_PIXEL, "MUEHEHE");
    if (!scene->data.win_ptr)
        ft_error("Creating window", scene, EXIT_FAILURE);
    scene->data.img_ptr = mlx_new_image(scene->data.mlx_ptr, CANVAS_PIXEL, CANVAS_PIXEL);
    if (!scene->data.img_ptr)
        ft_error("Creating image", scene, EXIT_FAILURE);
    scene->data.img_data = mlx_get_data_addr(scene->data.img_ptr, &scene->data.bpp, &scene->data.size_line, &scene->data.endian);
}

void close_window(t_data *data) {
    if (data->win_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    if (data->img_ptr)
        mlx_destroy_image(data->mlx_ptr, data->img_ptr);
    exit(0);
}

int key_hook(int keycode, t_data *data) {
    if (keycode == ESC_KEY)
        close_window(data);
    return (0);
}

int close_hook(t_data *data) {
    close_window(data);
    return (0);
}
