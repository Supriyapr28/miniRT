/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 17:47:25 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 12:00:00 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <float.h>
#include <math.h>

static void	build_cylinder_quad(const t_ray *ray, const t_cylinder *cyl,
			t_cyl_quad *q)
{
	q->oc = vec3_sub(ray->origin, cyl->origin);
	q->d_dot_a = vec3_dot(ray->direction, cyl->orientation);
	q->oc_dot_a = vec3_dot(q->oc, cyl->orientation);
	q->d_perp = vec3_sub(ray->direction,
			vec3_scale(cyl->orientation, q->d_dot_a));
	q->oc_perp = vec3_sub(q->oc,
			vec3_scale(cyl->orientation, q->oc_dot_a));
	q->a = vec3_dot(q->d_perp, q->d_perp);
	q->b = 2.0 * vec3_dot(q->d_perp, q->oc_perp);
	q->c = vec3_dot(q->oc_perp, q->oc_perp)
		- cyl->radius * cyl->radius;
}

static bool	solve_cylinder_quadratic(const t_ray *ray,
			const t_cylinder *cyl, t_range range, double *out_t)
{
	t_cyl_quad	q;
	double		discriminant;
	double		sqrt_d;
	double		t;

	build_cylinder_quad(ray, cyl, &q);
	if (vec3_abs(q.a) < 1e-15)
		return (false);
	discriminant = q.b * q.b - 4.0 * q.a * q.c;
	if (discriminant < 0.0)
		return (false);
	sqrt_d = sqrt(discriminant);
	t = (-q.b - sqrt_d) / (2.0 * q.a);
	if (t < range.min || t > range.max)
	{
		t = (-q.b + sqrt_d) / (2.0 * q.a);
		if (t < range.min || t > range.max)
			return (false);
	}
	*out_t = t;
	return (true);
}

static bool	intersect_lateral(const t_ray *ray, const t_cylinder *cyl,
			t_range range, t_cyl_lateral_hit *hit)
{
	double	t;
	t_vec3	p;
	t_vec3	axis_vec;
	double	axis_dist;

	if (!solve_cylinder_quadratic(ray, cyl, range, &t))
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

bool	hit_cylinder(const t_cylinder *cyl, const t_ray *ray,
			t_range range, t_hit *hit)
{
	t_cap_hit			best;
	t_vec3				axis_point;
	t_cyl_lateral_hit	lateral_hit;

	best = (t_cap_hit){DBL_MAX, {0, 0, 0}, {0, 0, 0}};
	if (intersect_lateral(ray, cyl, range, &lateral_hit))
	{
		best.t = lateral_hit.t;
		best.point = lateral_hit.point;
		axis_point = vec3_scale(cyl->orientation, lateral_hit.axis_dist);
		axis_point = vec3_add(cyl->origin, axis_point);
		best.normal = vec3_normalize(vec3_sub(lateral_hit.point, axis_point));
	}
	check_caps(ray, cyl, range, &best);
	if (best.t == DBL_MAX)
		return (false);
	hit->t = (float)best.t;
	hit->point = best.point;
	hit->normal = vec3_normalize(best.normal);
	hit->color = cyl->color;
	return (true);
}
