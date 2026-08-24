/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:17:32 by spaipur-          #+#    #+#             */
/*   Updated: 2026/08/17 15:36:13 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"rt.h"
#include "objects.h"
#include "parse.h"
#include<float.h>
#include<math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static t_vec3 camera_world_up(const t_vec3 forward)
{
    if (vec3_abs(vec3_dot(forward, (t_vec3){0.0, 1.0, 0.0})) > 0.999)
        return ((t_vec3){0.0, 0.0, 1.0});
    return ((t_vec3){0.0, 1.0, 0.0});
}

t_ray make_camera_ray(const t_scene *scene, int x, int y)
{
    t_vec3 forward;
    t_vec3 right;
    t_vec3 up;
    t_ray ray;
    double fov;
    ray.origin = scene->camera.coordinates;
    forward = vec3_normalize(scene->camera.direction);
    right = vec3_normalize(vec3_cross(camera_world_up(forward), forward));
    up = vec3_normalize(vec3_cross(forward, right));
    fov = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
    ray.direction = vec3_add(forward,
        vec3_scale(right,
            ((((double)x + 0.5) / (double)WIN_WIDTH) * 2.0 - 1.0) * fov * ((double)WIN_WIDTH / (double)WIN_HEIGHT)));
    ray.direction = vec3_add(ray.direction,
        vec3_scale(up,
            ((1.0 - (((double)y + 0.5) / (double)WIN_HEIGHT) * 2.0)) * fov));
    ray.direction = vec3_add(ray.direction, forward);
    ray.direction = vec3_normalize(ray.direction);
    return (ray);
}

t_vec3 ray_at(t_ray ray, double t)
{
    return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}

double ray_plane_intersection(t_ray ray, t_vec3 plane_point, t_vec3 plane_normal)
{
    double denom;
    double numerator;
    double t;

    denom = vec3_dot(ray.direction, plane_normal);
    if (vec3_abs(denom) < 1e-12)
        return (DBL_MAX);
    numerator = vec3_dot(vec3_sub(plane_point, ray.origin), plane_normal);
    t = numerator / denom;
    if (t < 0.0)
        return (DBL_MAX);
    return (t);
}

bool hit_plane(t_plane *pl, const t_ray *ray, double t_min, double t_max, t_hit *hit)
{
    double t = ray_plane_intersection(*ray, pl->origin, pl->normal);

    if (t < t_min || t > t_max)
        return false;

    hit->t = t;
    hit->point = ray_at(*ray, t);
    hit->normal = pl->normal;
    hit->color = pl->color;

    return true;
}

bool hit_sphere(const t_sphere *sphere, const t_ray *ray, float t_min, float t_max, t_hit *hit)
{
    t_vec3 oc = vec3_sub(ray->origin, sphere->center);
    
    double a = vec3_dot(ray->direction, ray->direction);
    double b = 2.0*vec3_dot(oc, ray->direction);
    double c = vec3_dot(oc, oc)-sphere->radius*sphere->radius;

    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0)
        return false;
    double sqrt_d = sqrt(discriminant);
    
    double t = (-b-sqrt_d)/(2.0 * a);
    
    if (t < t_min || t > t_max)
    {
        t = (-b + sqrt_d) / (2.0 * a);
        if (t < t_min || t > t_max)
            return (false);
    }
    hit->t = (float)t;
    hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t)); //actual hit pt
    hit->normal = vec3_normalize(vec3_sub(hit->point, sphere->center)); //direc frm sphere center to hit pt
    hit->color = sphere->color;
    return true;    
}

