/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:17:32 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 12:00:00 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <float.h>
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_ray	make_camera_ray(const t_scene *scene, int x, int y)
{
	t_ray			ray;
	double			fov;
	double			u;
	t_camera_basis	basis;

	ray.origin = scene->camera.coordinates;
	basis = camera_get_basis(&scene->camera);
	fov = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	u = (((double)x + 0.5) / (double)WIN_WIDTH) * 2.0 - 1.0;
	ray.direction = vec3_scale(basis.right,
			u * fov * ((double)WIN_WIDTH / (double)WIN_HEIGHT));
	u = 1.0 - (((double)y + 0.5) / (double)WIN_HEIGHT) * 2.0;
	ray.direction = vec3_add(basis.forward, ray.direction);
	ray.direction = vec3_add(ray.direction,
			vec3_scale(basis.up, u * fov));
	ray.direction = vec3_add(ray.direction, basis.forward);
	ray.direction = vec3_normalize(ray.direction);
	return (ray);
}

t_vec3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}

double	ray_plane_intersection(t_ray ray, t_vec3 plane_point,
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
	hit->point = ray_at(*ray, t);
	hit->normal = pl->normal;
	hit->color = pl->color;
	return (true);
}
