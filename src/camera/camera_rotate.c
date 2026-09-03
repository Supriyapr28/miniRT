/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:11:55 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 14:11:57 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	camera_rotate_yaw(t_camera *camera, double angle)
{
	t_camera_basis	basis;

	basis = camera_get_basis(camera);
	basis.up = vec3_scale(basis.up, angle);
	basis.up = vec3_add(camera->direction, basis.up);
	camera->direction = vec3_normalize(basis.up);
}

void	camera_rotate_pitch(t_camera *camera, double angle)
{
	t_camera_basis	basis;

	basis = camera_get_basis(camera);
	basis.right = vec3_scale(basis.right, angle);
	basis.right = vec3_add(camera->direction, basis.right);
	camera->direction = vec3_normalize(basis.right);
}

void	camera_rotate_roll(t_camera *camera, double angle)
{
	t_camera_basis	basis;

	basis = camera_get_basis(camera);
	basis.forward = vec3_scale(basis.forward, angle);
	basis.forward = vec3_add(camera->direction, basis.forward);
	camera->direction = vec3_normalize(basis.forward);
}
