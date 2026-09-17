/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:11:55 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/16 11:08:18 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void	rotate_around_axis(t_camera *camera, t_vec3 axis, double angle)
{
	t_vec3	rotated;

	rotated = vec3_add(camera->direction,
			vec3_scale(axis, angle));
	camera->direction = vec3_normalize(rotated);
}

void	camera_rotate_yaw(t_camera *camera, double angle)
{
	t_camera_basis	basis;

	basis = camera_get_basis(camera);
	rotate_around_axis(camera, basis.up, angle);
}

void	camera_rotate_pitch(t_camera *camera, double angle)
{
	t_camera_basis	basis;

	basis = camera_get_basis(camera);
	rotate_around_axis(camera, basis.right, angle);
}
