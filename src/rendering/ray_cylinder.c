/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 17:47:25 by uvadakku          #+#    #+#             */
/*   Updated: 2026/08/07 17:48:27 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <float.h>
#include <math.h>

/* Compute the lateral intersection of a ray with an infinite cylinder. */
static void build_cylinder_quad(const t_ray *ray, const t_cylinder *cyl, t_cyl_quad *q)
{
    q->oc       = vec3_sub(ray->origin, cyl->origin);
    q->d_dot_a  = vec3_dot(ray->direction, cyl->orientation);
    q->oc_dot_a = vec3_dot(q->oc, cyl->orientation);
    q->d_perp   = vec3_sub(ray->direction, vec3_scale(cyl->orientation, q->d_dot_a));
    q->oc_perp  = vec3_sub(q->oc, vec3_scale(cyl->orientation, q->oc_dot_a));
    q->a = vec3_dot(q->d_perp, q->d_perp);
    q->b = 2.0 * vec3_dot(q->d_perp, q->oc_perp);
    q->c = vec3_dot(q->oc_perp, q->oc_perp) - cyl->radius * cyl->radius;
}

static bool solve_cylinder_quadratic(const t_ray *ray, const t_cylinder *cyl, double t_min, double t_max, double *out_t)
{
    t_cyl_quad q;
    build_cylinder_quad(ray, cyl, &q);

    if (vec3_abs(q.a) < 1e-15)
        return (false);
    double disc = q.b * q.b - 4.0 * q.a * q.c;
    if (disc < 0.0)
        return (false);
    double sqrt_d = sqrt(disc);
    double t = (-q.b - sqrt_d) / (2.0 * q.a);
    if (t < t_min || t > t_max)
    {
        t = (-q.b + sqrt_d) / (2.0 * q.a);
        if (t < t_min || t > t_max)
            return (false);
    }
    *out_t = t;
    return (true);
}

static bool intersect_lateral(const t_ray *ray, const t_cylinder *cyl,
    double t_min, double t_max, t_cyl_lateral_hit *hit)
{
    double t;
    t_vec3 p;
    t_vec3 axis_vec;
    double axis_dist;

    if (!solve_cylinder_quadratic(ray, cyl, t_min, t_max, &t))
        return (false);
    p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
    axis_vec = vec3_sub(p, cyl->origin);
    axis_dist = vec3_dot(axis_vec, cyl->orientation);
    if (axis_dist < -cyl->half_height || axis_dist > cyl->half_height)
        return (false);
    hit->t = t;
    hit->point = p;
    hit->axis_dist = axis_dist;
    return (true);
}

bool hit_cylinder(const t_ray *ray, const t_cylinder *cyl, double t_min,
    double t_max, t_hit *hit)
{
    t_cap_hit best = {
        .t = DBL_MAX,
        .point = (t_vec3){0, 0, 0},
        .normal = (t_vec3){0, 0, 0}
    };
    t_cyl_lateral_hit lateral_hit;
    t_vec3 axis_point;

    if (intersect_lateral(ray, cyl, t_min, t_max, &lateral_hit))
    {
        best.t = lateral_hit.t;
        best.point = lateral_hit.point;
        axis_point = vec3_add(cyl->origin,
            vec3_scale(cyl->orientation, lateral_hit.axis_dist));
        best.normal = vec3_normalize(vec3_sub(lateral_hit.point, axis_point));
    }
    check_caps(ray, cyl, t_min, t_max, &best);
    if (best.t == DBL_MAX)
        return (false);
    hit->t = (float)best.t;
    hit->point = best.point;
    hit->normal = vec3_normalize(best.normal);
    hit->color = cyl->color;
    return (true);
}

