/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 12:00:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/01 13:05:43 by us               ###   ########.fr       */
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

/*
** Colors in a .rt file are 0-255 bytes, but while shading they act as
** *multipliers*, so each channel is mapped to 0.0 - 1.0 before it is
** applied to the surface color.
*/
static double color_ratio(int channel)
{
    if (channel <= 0)
        return (0.0);
    if (channel >= 255)
        return (1.0);
    return ((double)channel / 255.0);
}

static int clamp_channel(double value)
{
    if (value <= 0.0)
        return (0);
    if (value >= 255.0)
        return (255);
    return ((int)value);
}

/*
** Ambient light tints the surface, it does not replace it: a red object
** lit by a white ambient is dark red, never grey.
*/
static t_color compute_ambient(const t_scene *scene, const t_hit *hit)
{
    t_color ambient;
    double  ratio;

    ratio = scene->ambient.ratio;
    ambient.r = clamp_channel(hit->color.r * ratio
            * color_ratio(scene->ambient.color.r));
    ambient.g = clamp_channel(hit->color.g * ratio
            * color_ratio(scene->ambient.color.g));
    ambient.b = clamp_channel(hit->color.b * ratio
            * color_ratio(scene->ambient.color.b));
    return (ambient);
}

/*
** diffuse = surface_color * light_color * brightness * cos(normal, light_dir)
** so an "L x,y,z ratio 0,0,0" light contributes nothing at all.
*/
static t_color compute_diffuse(const t_scene *scene, const t_hit *hit)
{
    t_ray   shadow_ray;
    double  diff;
    t_color diffuse;

    shadow_ray = make_shadow_ray(hit, scene);
    if (is_occluded(scene, &shadow_ray, hit))
        return ((t_color){0, 0, 0});
    diff = vec3_dot(hit->normal, shadow_ray.direction);
    if (diff < 0.0)
        diff = 0.0;
    diff = diff * scene->light.brightness;
    diffuse.r = clamp_channel(hit->color.r * diff
            * color_ratio(scene->light.color.r));
    diffuse.g = clamp_channel(hit->color.g * diff
            * color_ratio(scene->light.color.g));
    diffuse.b = clamp_channel(hit->color.b * diff
            * color_ratio(scene->light.color.b));
    return (diffuse);
}

t_color shade(const t_scene *scene, const t_hit *hit)
{
    t_color ambient;
    t_color diffuse;
    t_color final_color;

    ambient = compute_ambient(scene, hit);
    diffuse = compute_diffuse(scene, hit);
    final_color.r = clamp_channel(ambient.r + diffuse.r);
    final_color.g = clamp_channel(ambient.g + diffuse.g);
    final_color.b = clamp_channel(ambient.b + diffuse.b);
    return (final_color);
}
