#include "iu_scene.h"

void open_window(t_data *data) {
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        ft_error("Initializing MiniLibX", data, EXIT_FAILURE);
    data->win_ptr = mlx_new_window(data->mlx_ptr, CANVAS_PIXEL, CANVAS_PIXEL, "MUEHEHE");
    if (!data->win_ptr)
        ft_error("Creating window", data, EXIT_FAILURE);
    data->img_ptr = mlx_new_image(data->mlx_ptr, 500, 500);
    if (!data->img_ptr)
        ft_error("Creating image", data, EXIT_FAILURE);
    data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp, &data->size_line, &data->endian);
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