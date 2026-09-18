/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cyl_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:52:14 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 12:00:00 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	try_cap_update(const t_ray *ray, const t_cap_params *cap,
			t_cap_hit *best)
{
	double	denom;
	double	numer;
	double	t;
	t_vec3	p;
	t_vec3	v;

	denom = vec3_dot(ray->direction, cap->normal);
	if (vec3_abs(denom) < 1e-12)
		return (false);
	numer = vec3_dot(vec3_sub(cap->center, ray->origin), cap->normal);
	t = numer / denom;
	if (t < cap->t_min || t > cap->t_max || t >= best->t)
		return (false);
	p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	v = vec3_sub(p, cap->center);
	if (vec3_dot(v, v) <= cap->radius * cap->radius)
	{
		best->t = t;
		best->point = p;
		best->normal = cap->normal;
		return (true);
	}
	return (false);
}

void	check_caps(const t_ray *ray, const t_cylinder *cyl,
			t_range range, t_cap_hit *best)
{
	t_cap_params	top;
	t_cap_params	bottom;

	top.center = vec3_add(cyl->origin,
			vec3_scale(cyl->orientation, cyl->half_height));
	top.normal = cyl->orientation;
	top.radius = cyl->radius;
	top.t_min = range.min;
	top.t_max = range.max;
	bottom.center = vec3_sub(cyl->origin,
			vec3_scale(cyl->orientation, cyl->half_height));
	bottom.normal = vec3_scale(cyl->orientation, -1.0);
	bottom.radius = cyl->radius;
	bottom.t_min = range.min;
	bottom.t_max = range.max;
	try_cap_update(ray, &top, best);
	try_cap_update(ray, &bottom, best);
}
