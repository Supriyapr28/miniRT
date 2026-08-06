/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:17:32 by spaipur-          #+#    #+#             */
/*   Updated: 2026/08/04 11:19:46 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"rt.h"
#include<float.h>

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