/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_axes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:03:52 by ybutkov           #+#    #+#             */
/*   Updated: 2026/09/14 17:56:12 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	project_axis(const t_camera *camera, t_vec3 axis, int *screen_x,
	int *screen_y)
{
	t_camera_basis	basis;
	double			x_proj;
	double			y_proj;

	basis = camera_get_basis(camera);
	x_proj = vec3_dot(axis, basis.right);
	y_proj = vec3_dot(axis, basis.up);
	*screen_x = (int)(x_proj * 45.0);
	*screen_y = (int)(-y_proj * 45.0);
}

static void	draw_axis_line(t_app *app, t_vec3 axis, int color)
{
	t_line_draw	line;
	int			end_x;
	int			end_y;
	int			center_x;
	int			center_y;

	center_x = WIN_WIDTH - 75;
	center_y = 65;
	project_axis(&app->scene->camera, axis, &end_x, &end_y);
	line.mlx = app->mlx;
	line.x0 = center_x;
	line.y0 = center_y;
	line.x1 = center_x + end_x;
	line.y1 = center_y + end_y;
	line.color = color;
	draw_line_internal(&line);
}

void	draw_axes(t_app *app)
{
	if (app == NULL || app->mlx == NULL || app->scene == NULL)
		return ;
	draw_axis_line(app, (t_vec3){1.0, 0.0, 0.0}, 0xFF0000);
	draw_axis_line(app, (t_vec3){0.0, 1.0, 0.0}, 0x00FF00);
	draw_axis_line(app, (t_vec3){0.0, 0.0, 1.0}, 0x0000FF);
	draw_object_markers(app);
}
