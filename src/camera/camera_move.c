/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:11:55 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 14:11:57 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void	camera_translate(t_camera *camera, t_vec3 axis, double amount)
{
	t_vec3	translation;

	translation = vec3_scale(axis, amount);
	camera->coordinates = vec3_add(camera->coordinates, translation);
}

void	camera_move_up(t_camera *camera, double amount)
{
	t_camera_basis	basis;

	basis = camera_get_basis(camera);
	camera_translate(camera, basis.up, amount);
}

void	camera_move_left(t_camera *camera, double amount)
{
	t_camera_basis	basis;

	basis = camera_get_basis(camera);
	camera_translate(camera, basis.right, -amount);
}

void	camera_zoom(t_camera *camera, double amount)
{
	t_camera_basis	basis;

	basis = camera_get_basis(camera);
	camera_translate(camera, basis.forward, amount);
}
