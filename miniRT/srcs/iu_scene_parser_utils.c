#include "iu_scene.h"

static int parse_int(const char **str) {
    int num = 0, sign = 1;
    if (**str == '-') { sign = -1; (*str)++; }
    while (**str >= '0' && **str <= '9') {
        num = num * 10 + (**str - '0');
        (*str)++;
    }
    return num * sign;
}

static float parse_float(const char **str) {
    float result = 0.0;
    float factor = 1.0;
    int sign = 1;
    
    if (**str == '-') { sign = -1; (*str)++; }
    
    // Parse integer part
    while (**str >= '0' && **str <= '9') {
        result = result * 10.0 + (**str - '0');
        (*str)++;
    }
    
    // Parse fractional part
    if (**str == '.') {
        (*str)++;
        while (**str >= '0' && **str <= '9') {
            result = result + (**str - '0') * (factor *= 0.1f);
            (*str)++;
        }
    }
    
    return result * sign;
}

static void skip_spaces(const char **str) {
    while (**str == ' ' || **str == '\t') (*str)++;
}

static void parse_color(const char **str, t_color *color, t_scene *scene) {
    color->r = parse_int(str);
    if (color->r < 0 || color->r > 255) 
        ft_error("Color R out of range [0, 255]", scene->data, EXIT_FAILURE);
    (*str)++; // skip comma
    color->g = parse_int(str);
    if (color->g < 0 || color->g > 255)
        ft_error("Color G out of range [0, 255]", scene->data, EXIT_FAILURE);
    (*str)++; // skip comma
    if (color->b < 0 || color->b > 255)
        ft_error("Color B out of range [0, 255]", scene->data, EXIT_FAILURE);
    color->b = parse_int(str);
}
