/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 12:19:41 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/07 11:21:58 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <float.h>

static double	ray_plane_intersection(t_ray ray, t_vec3 plane_point,
			t_vec3 plane_normal)
{
	double	denom;
	double	numerator;
	double	t;

	denom = vec3_dot(ray.direction, plane_normal);
	if (vec3_abs(denom) < 1e-12)
		return (DBL_MAX);
	numerator = vec3_dot(vec3_sub(plane_point, ray.origin),
			plane_normal);
	t = numerator / denom;
	if (t < 0.0)
		return (DBL_MAX);
	return (t);
}
bool	hit_plane(const t_plane *pl, const t_ray *ray, t_range range,
		t_hit *hit)
{
	double	t;

	t = ray_plane_intersection(*ray, pl->origin, pl->normal);
	if (t < range.min || t > range.max)
		return (false);
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->normal = pl->normal;
	hit->color = pl->color;
	return (true);
}

static bool	check_object_hit(t_object *obj, const t_ray *ray,
			t_range range, t_hit *hit_info)
{
	if (obj->type == OBJ_PLANE)
		return (hit_plane(&obj->u_data.plane, ray, range, hit_info));
	if (obj->type == OBJ_CYLINDER)
		return (hit_cylinder(&obj->u_data.cylinder, ray, range, hit_info));
	if (obj->type == OBJ_SPHERE)
		return (hit_sphere(&obj->u_data.sphere, ray, range, hit_info));
	return (false);
}

bool	find_hit(const t_scene *scene, const t_ray *ray,
			t_hit *closest_hit)
{
	t_object	*current;
	t_hit		temp_hit;
	t_range		range;
	bool		hit_anything;

	closest_hit->t = DBL_MAX;
	current = scene->object;
	hit_anything = false;
	while (current != NULL)
	{
		range.min = 0.001;
		range.max = closest_hit->t;
		if (check_object_hit(current, ray, range, &temp_hit))
		{
			*closest_hit = temp_hit;
			hit_anything = true;
		}
		current = current->next;
	}
	return (hit_anything);
}


