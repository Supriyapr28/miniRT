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

# include "camera.h"
/*
** Picking a reference "up" for the camera frame. Y is the natural choice,
** but it collapses when the camera looks straight up or down (the cross
** product with a parallel vector is zero), so Z takes over in that case.
*/
t_vec3 camera_world_up(t_vec3 forward)
{
    if (vec3_abs(vec3_dot(forward, (t_vec3){0.0, 1.0, 0.0})) > 0.999)
        return ((t_vec3){0.0, 0.0, 1.0});
    return ((t_vec3){0.0, 1.0, 0.0});
}

t_camera_basis camera_get_basis(const t_camera *camera)
{
    t_camera_basis basis;

    basis.forward = vec3_normalize(camera->direction);
    basis.right = vec3_normalize(vec3_cross(basis.forward,
                camera_world_up(basis.forward)));
    basis.up = vec3_normalize(vec3_cross(basis.right, basis.forward));
    return (basis);
}

void camera_translate(t_camera *camera, t_vec3 axis, double amount)
{
    camera->coordinates = vec3_add(camera->coordinates,
            vec3_scale(axis, amount));
}

void camera_move_up(t_camera *camera, double amount)
{
    t_camera_basis basis;

    basis = camera_get_basis(camera);
    camera_translate(camera, basis.up, amount);
}

void camera_move_left(t_camera *camera, double amount)
{
    t_camera_basis basis;

    basis = camera_get_basis(camera);
    camera_translate(camera, basis.right, -amount);
}
void camera_zoom(t_camera *camera, double amount)
{
    t_camera_basis basis;

    basis = camera_get_basis(camera);
    camera_translate(camera, basis.forward, amount);
}
//EXPERIMENTAL: Rotate camera around its own axes
/*void camera_rotate(t_camera *camera, t_vec3 axis, double pitch)
{
    t_camera_basis basis;
    t_vec3 new_direction;

    basis = camera_get_basis(camera);
    new_direction = vec3_add(vec3_scale(basis.right, yaw),
            vec3_scale(basis.up, pitch));
    camera->direction = vec3_normalize(vec3_add(camera->direction, new_direction));
}*/

void camera_rotate_yaw(t_camera *camera, double angle)
{
    t_camera_basis basis;
    t_vec3 new_direction;

    basis = camera_get_basis(camera);
    new_direction = vec3_scale(basis.up, angle);
    camera->direction = vec3_normalize(vec3_add(camera->direction, new_direction));
}

void camera_rotate_pitch(t_camera *camera, double angle)
{
    t_camera_basis basis;
    t_vec3 new_direction;

    basis = camera_get_basis(camera);
    new_direction = vec3_scale(basis.right, angle);
    camera->direction = vec3_normalize(vec3_add(camera->direction, new_direction));
}

void camera_rotate_roll(t_camera *camera, double angle)
{
    t_camera_basis basis;
    t_vec3 new_direction;

    basis = camera_get_basis(camera);
    new_direction = vec3_scale(basis.forward, angle);
    camera->direction = vec3_normalize(vec3_add(camera->direction, new_direction));
}
