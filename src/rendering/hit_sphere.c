/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 12:00:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/18 10:49:14 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <math.h>

static bool	intersect_sphere(const t_sphere *sphere, const t_ray *ray,
			t_range range, double *t)
{
	t_vec3			oc;
	t_quad_params	params;

	oc = vec3_sub(ray->origin, sphere->center);
	params.a = vec3_dot(ray->direction, ray->direction);
	params.b = 2.0 * vec3_dot(oc, ray->direction);
	params.c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	params.range = range;
	return (solve_quadratic(&params, t));
}

bool	hit_sphere(const t_sphere *sphere, const t_ray *ray,
			t_range range, t_hit *hit)
{
	double	t;

	if (!intersect_sphere(sphere, ray, range, &t))
		return (false);
	hit->t = (float)t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->normal = vec3_normalize(vec3_sub(hit->point, sphere->center));
	hit->color = sphere->color;
	return (true);
}
