/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 17:39:05 by us                #+#    #+#             */
/*   Updated: 2026/09/09 10:44:23 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#ifdef __APPLE__
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_PITCH_DOWN 125
# define KEY_LEFT 124
# define KEY_RIGHT 123
# define KEY_IN 34
# define KEY_OUT 31
# define KEY_YAW_A 13
# define KEY_YAW_C 12
# define KEY_PITCH_C 1
# define KEY_PITCH_A 2
# define KEY_RESET 15 // reset camera and objects
#else
# define KEY_ESC 65307 //exit
# define KEY_UP 65362 //camera up
# define KEY_PITCH_DOWN 65364 //camera down
# define KEY_LEFT 65361 //camera left
# define KEY_RIGHT 65363 //camera right
# define KEY_IN 61 //camera in
# define KEY_OUT 45 //camera out
# define KEY_PITCH_W 119 //ROTATE pitch up
# define KEY_PITCH_Q 113 //ROTATE pitch down
# define KEY_YAW_S 115 // yaw left
# define KEY_YAW_D 100 // yaw right
# define KEY_RESET 114 // reset camera and objects
#endif

bool		handle_object_key(int keycode, t_object *object);

static bool	handle_move_key(int keycode, t_camera *camera)
{
	if (keycode == KEY_UP)
		camera_move_up(camera, CAM_STEP);
	else if (keycode == KEY_PITCH_DOWN)
		camera_move_up(camera, -CAM_STEP);
	else if (keycode == KEY_LEFT)
		camera_move_left(camera, -CAM_STEP);
	else if (keycode == KEY_RIGHT)
		camera_move_left(camera, CAM_STEP);
	else if (keycode == KEY_IN)
		camera_zoom(camera, CAM_STEP);
	else if (keycode == KEY_OUT)
		camera_zoom(camera, -CAM_STEP);
	else
		return (false);
	return (true);
}

static bool	handle_rotate_key(int keycode, t_camera *camera)
{
	if (keycode == KEY_YAW_S)
		camera_rotate_pitch(camera, -0.1);
	else if (keycode == KEY_YAW_D)
		camera_rotate_pitch(camera, 0.1);
	else if (keycode == KEY_PITCH_W)
		camera_rotate_yaw(camera, -0.1);
	else if (keycode == KEY_PITCH_Q)
		camera_rotate_yaw(camera, 0.1);
	else
		return (false);
	return (true);
}

static bool	apply_camera_key(int keycode, t_camera *camera)
{
	if (handle_move_key(keycode, camera))
	{
		return (true);
	}
	if (handle_rotate_key(keycode, camera))
		return (true);
	return (false);
}

int	handle_key(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app == NULL || app->scene == NULL)
		return (0);
	if (keycode == KEY_ESC)
	{
		destroy_app(app);
		exit(0);
	}
	if (keycode == KEY_RESET)
	{
		reset_scene_state(app);
		render_frame(app);
		return (0);
	}
	if (handle_object_key(keycode, app->selected_object))
	{
		render_frame(app);
		return (0);
	}
	if (apply_camera_key(keycode, &app->scene->camera))
		render_frame(app);
	return (0);
}

int	handle_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	destroy_app(app);
	exit(0);
	return (0);
}
