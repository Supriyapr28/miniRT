/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:17:32 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/14 17:38:19 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <float.h>
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static t_vec3	camera_world_up(t_vec3 forward)
{
	if (vec3_abs(vec3_dot(forward, (t_vec3){0.0, 1.0, 0.0})) > 0.999)
		return ((t_vec3){0.0, 0.0, 1.0});
	return ((t_vec3){0.0, 1.0, 0.0});
}

t_camera_basis	camera_get_basis(const t_camera *camera)
{
	t_camera_basis	basis;

	if (camera == NULL)
		return ((t_camera_basis){(t_vec3){0.0, 0.0, 0.0},
			(t_vec3){0.0, 0.0, 0.0}, (t_vec3){0.0, 0.0, 0.0}});
	basis.forward = vec3_normalize(camera->direction);
	basis.up = camera_world_up(basis.forward);
	basis.right = vec3_cross(basis.up, basis.forward);
	basis.right = vec3_normalize(basis.right);
	basis.up = vec3_cross(basis.forward, basis.right);
	basis.up = vec3_normalize(basis.up);
	return (basis);
}

t_ray	shoot_ray(const t_scene *scene, int x, int y)
{
	t_camera_basis	basis;
	t_ray			ray;
	double			fov;

	ray.origin = scene->camera.coordinates;
	basis = camera_get_basis(&scene->camera);
	fov = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	ray.direction = vec3_add(basis.forward,
			vec3_scale(basis.right,
				((((double)x + 0.5) / (double)WIN_WIDTH) * 2.0 - 1.0)
				* fov * ((double)WIN_WIDTH / (double)WIN_HEIGHT)));
	ray.direction = vec3_add(ray.direction,
			vec3_scale(basis.up,
				((1.0 - (((double)y + 0.5) / (double)WIN_HEIGHT)
						* 2.0)) * fov));
	ray.direction = vec3_normalize(ray.direction);
	return (ray);
}
