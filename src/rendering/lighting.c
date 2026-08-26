/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 12:00:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/08/26 17:02:44 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

static bool shadow_hit_object(const t_object *object, const t_ray *ray, double light_dist)
{
    t_hit	hit;

    if (object->type == OBJ_SPHERE)
        return (hit_sphere(&object->u.sphere, ray, 0.001, light_dist, &hit));
    if (object->type == OBJ_PLANE)
        return (hit_plane(&object->u.plane, ray, 0.001, light_dist, &hit));
    if (object->type == OBJ_CYLINDER)
        return (hit_cylinder(&object->u.cylinder, ray, 0.001, light_dist, &hit));
    return (false);
}

static t_ray make_shadow_ray(const t_hit *hit, const t_scene *scene)
{
	t_ray shadow;
	
    shadow.origin = vec3_add(hit->point, vec3_scale(hit->normal, 0.001));
	shadow.direction = vec3_normalize(vec3_sub(scene->light.origin, hit->point));
	return shadow;
}

static bool is_occluded(const t_scene *scene, const t_ray *shadow_ray, const t_hit *hit)
{
    double light_dist;
    t_object *current;

    light_dist = vec3_length(vec3_sub(scene->light.origin, hit->point));
    current = scene->object;
    while (current != NULL)
    {
        if (shadow_hit_object(current, shadow_ray, light_dist))
            return (true);
        current = current->next;
    }
    return (false);
}


static t_color compute_ambient(const t_scene *scene)
{
    t_color ambient;

    ambient.r = (int)(scene->ambient.ratio * scene->ambient.color.r);
    ambient.g = (int)(scene->ambient.ratio * scene->ambient.color.g);
    ambient.b = (int)(scene->ambient.ratio * scene->ambient.color.b);
    return (ambient);
}

static t_color compute_diffuse(const t_scene *scene, const t_hit *hit)
{
    t_vec3  light_dir;
    double  diff;
    t_color diffuse;

    t_ray shadow_ray = make_shadow_ray(hit, scene);
    if (is_occluded(scene, &shadow_ray, hit))
        return (t_color){0, 0, 0};
    light_dir = shadow_ray.direction;
    diff = vec3_dot(hit->normal, light_dir);
    if (diff < 0.0)
        diff = 0.0;
    diffuse.r = (int)(hit->color.r * diff * scene->light.brightness);
    diffuse.g = (int)(hit->color.g * diff * scene->light.brightness);
    diffuse.b = (int)(hit->color.b * diff * scene->light.brightness);
    return (diffuse);
}

t_color shade(const t_scene *scene, const t_hit *hit)
{
    t_color ambient;
    t_color diffuse;
    t_color final_color;

    ambient = compute_ambient(scene);
    diffuse = compute_diffuse(scene, hit);
    final_color.r = ambient.r + diffuse.r;
    final_color.g = ambient.g + diffuse.g;
    final_color.b = ambient.b + diffuse.b;
    return (final_color);
}
