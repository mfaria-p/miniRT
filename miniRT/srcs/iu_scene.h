#ifndef SCENE_H
#define SCENE_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "minirt.h"

#define ESC_KEY 65307

typedef struct s_data {
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img_data;
    int bpp;
    int size_line;
    int endian;
    int fd;
} t_data;

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_ambient {
    float ratio;
    t_color color;
} t_ambient;

typedef struct s_camera {
    float x, y, z;
    float orient_x, orient_y, orient_z;
    int fov;
} t_camera;

typedef struct s_light {
    float x, y, z;
    float brightness;
    t_color color;
} t_light;

typedef struct s_sphere {
    float x, y, z;
    float diameter;
    t_color color;
} t_sphere;

typedef struct s_plane {
    float x, y, z;
    float orient_x, orient_y, orient_z;
    t_color color;
} t_plane;

typedef struct s_cylinder {
    float x, y, z;
    float orient_x, orient_y, orient_z;
    float diameter;
    float height;
    t_color color;
} t_cylinder;

typedef struct s_scene {
    t_data data;
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_sphere *spheres;
    int sphere_count;
    t_plane *planes;
    int plane_count;
    t_cylinder *cylinders;
    int cylinder_count;
} t_scene;

#endif
