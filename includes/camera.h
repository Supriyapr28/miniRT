/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 15:58:56 by us                #+#    #+#             */
/*   Updated: 2026/09/14 17:38:36 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "parse.h"
# include "objects.h"

# define CAM_STEP 0.5

typedef struct s_camera_basis
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
}	t_camera_basis;

t_vec3			camera_world_up(t_vec3 forward);
t_camera_basis	camera_get_basis(const t_camera *camera);
t_vec3			camera_world_up(t_vec3 forward);
void			camera_move_up(t_camera *camera, double amount);
void			camera_move_left(t_camera *camera, double amount);
void			camera_zoom(t_camera *camera, double amount);
void			camera_rotate_yaw(t_camera *camera, double angle);
void			camera_rotate_pitch(t_camera *camera, double angle);

#endif
