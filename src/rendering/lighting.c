/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 12:00:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 12:00:00 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool	shadow_hit_object(const t_object *object, const t_ray *ray,
			double light_dist)
{
	t_hit	hit;
	t_range	range;

	range.min = 0.001;
	range.max = light_dist;
	if (object->type == OBJ_SPHERE)
		return (hit_sphere(&object->u_data.sphere, ray, range, &hit));
	if (object->type == OBJ_PLANE)
		return (hit_plane(&object->u_data.plane, ray, range, &hit));
	if (object->type == OBJ_CYLINDER)
		return (hit_cylinder(&object->u_data.cylinder, ray, range, &hit));
	return (false);
}

static bool	is_occluded(const t_scene *scene, const t_ray *shadow_ray,
			const t_hit *hit)
{
	double		light_dist;
	t_object	*current;

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

static t_color	compute_ambient(const t_scene *scene, const t_hit *hit)
{
	t_color	ambient;
	double	ratio;

	ratio = scene->ambient.ratio;
	ambient.r = clamp_channel(hit->color.r * ratio
			* color_ratio(scene->ambient.color.r));
	ambient.g = clamp_channel(hit->color.g * ratio
			* color_ratio(scene->ambient.color.g));
	ambient.b = clamp_channel(hit->color.b * ratio
			* color_ratio(scene->ambient.color.b));
	return (ambient);
}

static t_color	compute_diffuse(const t_scene *scene, const t_hit *hit)
{
	t_ray	shadow_ray;
	double	diff;
	t_color	diffuse;

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

t_color	shade(const t_scene *scene, const t_hit *hit)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	final_color;

	ambient = compute_ambient(scene, hit);
	diffuse = compute_diffuse(scene, hit);
	final_color.r = clamp_channel(ambient.r + diffuse.r);
	final_color.g = clamp_channel(ambient.g + diffuse.g);
	final_color.b = clamp_channel(ambient.b + diffuse.b);
	return (final_color);
}
