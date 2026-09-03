/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 16:24:26 by us                #+#    #+#             */
/*   Updated: 2026/09/01 20:36:36 by us               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static t_vec3	camera_world_up(t_vec3 forward)
{
	if (vec3_abs(vec3_dot(forward, (t_vec3){0.0, 1.0, 0.0})) > 0.999)
		return ((t_vec3){0.0, 0.0, 1.0});
	return ((t_vec3){0.0, 1.0, 0.0});
}

t_camera_basis	camera_get_basis(const t_camera *camera)
{
	t_camera_basis	basis;

	basis.forward = vec3_normalize(camera->direction);
	basis.up = camera_world_up(basis.forward);
	basis.right = vec3_cross(basis.forward, basis.up);
	basis.right = vec3_normalize(basis.right);
	basis.up = vec3_cross(basis.right, basis.forward);
	basis.up = vec3_normalize(basis.up);
	return (basis);
}
