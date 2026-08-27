/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 12:00:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/08/25 16:59:16 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

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

    light_dir = vec3_normalize(vec3_sub(scene->light.origin, hit->point));
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
