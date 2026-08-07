#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_ray
{
    t_vec3 origin;
    t_vec3 direction;
} t_ray;

typdef struct s_hit
{
    float t;
    t_vec3 point;
    t_vec3 normal;
    t_color color;
} t_hit;
#endif 