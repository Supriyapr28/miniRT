/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:17:32 by spaipur-          #+#    #+#             */
/*   Updated: 2026/08/07 17:51:11 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"rt.h"
#include "objects.h"
#include "parse.h"
#include<float.h>
#include<math.h>

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

