#include "iu_scene.h"

int ft_checkfile(char * file, t_data *data)
{
    data->fd = open(file, O_RDONLY, 0444);
    if (data->fd == -1)
    {
        ft_error("Invalid file", data, EXIT_FAILURE);
    }
}