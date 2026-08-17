/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cyl_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:52:14 by uvadakku          #+#    #+#             */
/*   Updated: 2026/08/17 16:50:35 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool try_cap_update(const t_ray *ray, const t_cap_params *cap, t_cap_hit *best)
{
	double denom = vec3_dot(ray->direction, cap->normal);
	if (vec3_abs(denom) < 1e-12)
		return (false); /* parallel */

	double numer = vec3_dot(vec3_sub(cap->center, ray->origin), cap->normal);
	double t = numer/denom;
	
	if (t < cap->t_min || t > cap->t_max)
		return (false);
	if (t >= best->t)
		return (false); /* not closer */

	t_vec3 p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	t_vec3 v = vec3_sub(p, cap->center); /*pt lies inside circular disk*/

	if (vec3_dot(v, v) <= cap->radius * cap->radius)
	{
		best->t     = t;
		best->point = p;
		best->normal = cap->normal;
		return (true);
	}
	return (false); //outside disk
}

void check_caps(const t_ray *ray, const t_cylinder *cyl, double t_min, double t_max, t_cap_hit *best)
{
	t_cap_params top = {
		.center = vec3_add(cyl->origin, vec3_scale(cyl->orientation, cyl->half_height)),
		.normal = cyl->orientation,
		.radius = cyl->radius,
		.t_min = t_min,
		.t_max = t_max
	};

	t_cap_params bottom = {
		.center = vec3_sub(cyl->origin, vec3_scale(cyl->orientation, cyl->half_height)),
		.normal = vec3_scale(cyl->orientation, -1.0),
		.radius = cyl->radius,
		.t_min = t_min,
		.t_max = t_max
	};

	try_cap_update(ray, &top, best);
	try_cap_update(ray, &bottom, best);
}
