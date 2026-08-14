#ifndef OBJECTS_H
# define OBJECTS_H

# include <stdbool.h>

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

typedef struct s_hit
{
    double t;       //distance from ray origin to intersection
    t_vec3 point;  //exact intersection point in world space
    t_vec3 normal; //surface normal at the hit point
    t_color color; //obj color at hit
} t_hit;

typedef enum e_obj_type
{
    OBJ_AMBIENT,
    OBJ_CAMERA,
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER
} t_obj_type;

typedef struct s_sphere
{
    t_vec3  center;
    double  radius;
    t_color color;
} t_sphere;

typedef struct s_plane
{
    t_vec3  origin;
    t_vec3  normal;
    t_color color;
} t_plane;

typedef struct s_cylinder
{
    t_vec3  origin;
    t_vec3  orientation;
    double	radius;
    double  half_height;
    t_color color;
} t_cylinder;

typedef struct s_object
{
    t_obj_type type;
    union
    {
        t_sphere sphere;
        t_plane plane;
        t_cylinder cylinder;
    } u;
    t_color material;
    struct s_object *next;
} t_object;

typedef struct s_cyl_lateral_hit
{
    double t;
    t_vec3 point;
    double axis_dist;
} t_cyl_lateral_hit;

typedef struct s_cap_hit
{
    double t;
    t_vec3 point;
    t_vec3 normal;
} t_cap_hit;

typedef struct s_cyl_quad
{
    t_vec3 oc;
    double d_dot_a;
    double oc_dot_a;
    t_vec3 d_perp;
    t_vec3 oc_perp;
    double a;
    double b;
    double c;
} t_cyl_quad;

typedef struct s_cap_params
{
    t_vec3 center;
    t_vec3 normal;
    double radius;
    double t_min;
    double t_max;
} t_cap_params;


#endif 