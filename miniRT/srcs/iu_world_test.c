#include "minirt.h"

void print_vector(const t_vector *vec) {
    printf("  Vector: (%f, %f, %f)\n", vec->x, vec->y, vec->z);
}

void print_color(const t_vector *color) {
    printf("  Color: (R: %f, G: %f, B: %f)\n", color->x, color->y, color->z);
}

void print_light(const t_light_source *light) {
    printf("Light Source:\n");
    print_vector(&light->origin);
    print_color(&light->color);
    printf("  Intensity: %f\n", light->intensity);
}

void print_object(const t_object *object) {
    printf("Object:\n");
    print_vector(&object->translation);
    print_color(&object->material.color);
    printf("  Shape Type: %d\n", object->shape.type);
    printf("  Height: %f\n", object->shape.constant);
    printf("  Height: %f\n", object->shape.height);
}

void print_camera(const t_camera *camera) {
    if (!camera) {
        printf("Camera is NULL\n");
        return;
    }

    printf("Camera values:\n");
    printf("  Scale: %f\n", camera->scale);
    printf("  HSize: %f\n", camera->hsize);
    printf("  VSize: %f\n", camera->vsize);
    printf("  Pixel Size: %f\n", camera->pixel_size);
    printf("  Half Width: %f\n", camera->half_width);
    printf("  Half Height: %f\n", camera->half_height);
    printf("  Rotation Axis: (%f, %f, %f)\n", camera->rotation.axis.x, camera->rotation.axis.y, camera->rotation.axis.z);
    printf("  Rotation Angle: %f\n", camera->rotation.angle);
    printf("  Origin: (%f, %f, %f)\n", camera->origin.x, camera->origin.y, camera->origin.z);
    printf("  Axis: (%f, %f, %f)\n", camera->axis.x, camera->axis.y, camera->axis.z);
    printf("  FOV: %f\n", camera->fov);
}

void print_img(const t_img *img) {
    if (!img) {
        printf("Image is NULL\n");
        return;
    }

    printf("Image values:\n");
    printf("  Image Pointer: %p\n", img->img);
    printf("  Address: %p\n", img->addr);
    printf("  Bits Per Pixel: %d\n", img->bpp);
    printf("  Line Length: %d\n", img->len);
    printf("  Endian: %d\n", img->endian);
}

void print_world(const t_world *world) {
    if (!world) {
        printf("World is NULL\n");
        return;
    }

    printf("World Properties:\n");
    print_vector(&world->ray_origin);

    printf("Objects:\n");
    t_list *current = world->objects;
    while (current) {
        print_object((t_object *)current->content);
        current = current->next;
    }

    print_light(&world->light);
}
