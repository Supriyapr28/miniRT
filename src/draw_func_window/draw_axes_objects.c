/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_axes_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 00:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/09/17 00:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_internal.h"
#include "rt.h"

static int	color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static void	draw_marker_cross(t_mlx *mlx, int x, int y, int color)
{
	t_line_draw	line;

	line.mlx = mlx;
	line.color = color;
	line.x0 = x - 2;
	line.y0 = y;
	line.x1 = x + 2;
	line.y1 = y;
	draw_line_internal(&line);
	line.x0 = x;
	line.y0 = y - 2;
	line.x1 = x;
	line.y1 = y + 2;
	draw_line_internal(&line);
}

static void	draw_object_marker(t_app *app, t_object *object)
{
	t_vec3	*pos;
	t_vec3	direction;
	int		screen_x;
	int		screen_y;

	pos = object_get_position(object);
	if (pos == NULL)
		return ;
	direction = vec3_sub(*pos, app->scene->camera.coordinates);
	if (vec3_abs(vec3_length(direction)) < 1e-9)
		return ;
	direction = vec3_normalize(direction);
	project_axis(&app->scene->camera, direction, &screen_x, &screen_y);
	draw_marker_cross(app->mlx, WIN_WIDTH - 75 + screen_x, 65 + screen_y,
		color_to_int(object->material));
}

void	draw_object_markers(t_app *app)
{
	t_object	*current;

	current = app->scene->object;
	while (current != NULL)
	{
		draw_object_marker(app, current);
		current = current->next;
	}
}
