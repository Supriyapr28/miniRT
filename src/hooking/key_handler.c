/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 17:39:05 by us                #+#    #+#             */
/*   Updated: 2026/09/01 21:03:37 by us               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

# include <stdio.h>

#ifdef __APPLE__
# define KEY_ESC    53
# define KEY_UP     126
# define KEY_PITCH_AOWN   125
# define KEY_LEFT   124
# define KEY_RIGHT   123
# define KEY_IN     34
# define KEY_OUT    31
# define KEY_YAW_A      13
# define KEY_YAW_C      12
# define KEY_PITCH_C      1
# define KEY_PITCH_A      2
# define KEY_ROLL_A      7
# define KEY_ROLL_C      8
#else
# define KEY_ESC    65307
# define KEY_UP     65362
# define KEY_PITCH_AOWN   65364
# define KEY_LEFT   65361
# define KEY_RIGHT   65363
# define KEY_IN     61
# define KEY_OUT    45
# define KEY_YAW_A      119
# define KEY_YAW_C      113
# define KEY_PITCH_C      115
# define KEY_PITCH_A      100
#endif

static bool apply_camera_key(int keycode, t_camera *camera)
{

    printf("Keycode: %d\n", keycode);
    if (keycode == KEY_UP)
{
    camera_move_up(camera, CAM_STEP);
    return (true);
    }
    if (keycode == KEY_PITCH_AOWN)
    {
        camera_move_up(camera, -CAM_STEP);
        return (true);
    }
    if (keycode == KEY_LEFT)
    {
        camera_move_left(camera, -CAM_STEP);
        return (true);
    }
    if (keycode == KEY_RIGHT)
    {
        camera_move_left(camera, CAM_STEP);
        return (true);
    }
    if (keycode == KEY_IN)
    {
        camera_zoom(camera, CAM_STEP);
        return (true);
    }
    if (keycode == KEY_OUT)
    {
        camera_zoom(camera, -CAM_STEP);
        return (true);
    }
    if (keycode == KEY_YAW_A)
    {
        camera_rotate_pitch(camera, -0.1);
        return (true);
    }
    if (keycode == KEY_YAW_C)
    {
        
        camera_rotate_pitch(camera, 0.1);
        return (true);
    }
    if (keycode == KEY_PITCH_C)
    {
        camera_rotate_yaw(camera, -0.1);
        return (true);
    }
    if (keycode == KEY_PITCH_A)
    {
        camera_rotate_yaw(camera, 0.1);
        return (true);
    }
    return (false);
}

int handle_key(int keycode, void *param)
{
    t_app *app;

    app = (t_app *)param;
    if (keycode == KEY_ESC)
    {
        destroy_app(app);
        exit(0);
    }
    if (apply_camera_key(keycode, &app->scene->camera))
        render_frame(app);
    return (0);
}

int handle_close(void *param)
{
    t_app *app;

    app = (t_app *)param;
    destroy_app(app);
    exit(0);
    return (0);
}

