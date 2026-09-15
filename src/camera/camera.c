/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 16:24:26 by us                #+#    #+#             */
/*   Updated: 2026/09/14 17:39:27 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw_internal.h"
#include "camera.h"

t_vec3	camera_world_up(t_vec3 forward)
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
