#ifndef IU_SCENE_H
#define IU_SCENE_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "minirt.h"
#include "../libft/libft/ft_printf.h"
#include "../libft/libft/get_next_line.h"
#include "../libft/libft/libft.h"
#include "../minilibx-linux/mlx.h"

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
    int camera_count;
    int light_count;
    int ambient_count;
} t_scene;

//window related functions
void open_window(t_data *data);
void close_window(t_data *data);
int key_hook(int keycode, t_data *data);
int close_hook(t_data *data);

//error handling
void ft_checkfile(char * file, t_data *data);
void	is_invalid_file(t_scene *scene);
int ft_error(char *str, t_data *data, int e);

//checks before parsing functions
void check_ambient(const char *line, t_scene *scene);
void check_camera(const char *line, t_scene *scene) ;
void check_light(const char *line, t_scene *scene) ;
void check_sphere(const char *line, t_scene *scene) ;
void check_plane(const char *line, t_scene *scene) ;
void check_cylinder(const char *line, t_scene *scene) ;
void	check_vector(char ***str, t_scene *scene, int j);
void	check_colors(char ***str, t_scene *scene, int j);

//scene parsing functions
void parse_scene(const char *filename, t_scene *scene);
void parse_ambient(const char *line, t_scene *scene);
void parse_camera(const char *line, t_scene *scene);
void parse_light(const char *line, t_scene *scene);
void parse_sphere(const char *line, t_scene *scene);
void parse_plane(const char *line, t_scene *scene);
void parse_cylinder(const char *line, t_scene *scene);

//scene parsing utility functions
int parse_int(const char **str);
float parse_float(const char **str);
void skip_spaces(const char **str);
void parse_color(const char **str, t_color *color, t_scene *scene);
void *ft_realloc(void *ptr, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int	is_float(char *str);
int	is_int(char *str);
void	free_array(char *arr[]);
int	array_length(char *arr[]);

#endif
