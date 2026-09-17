/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 16:00:00 by uvadakku          #+#    #+#             */
/*   Updated: 2026/09/07 15:27:12 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <float.h>

static bool	hit_object(const t_object *object, const t_ray *ray,
		t_range range, t_hit *hit)
{
	if (object->type == OBJ_SPHERE)
		return (hit_sphere(&object->u_data.sphere, ray, range, hit));
	if (object->type == OBJ_PLANE)
		return (hit_plane(&object->u_data.plane, ray, range, hit));
	if (object->type == OBJ_CYLINDER)
		return (hit_cylinder(&object->u_data.cylinder, ray, range, hit));
	return (false);
}

static t_object	*pick_object(const t_scene *scene, const t_ray *ray)
{
	t_object	*object;
	t_object	*selected;
	t_hit		hit;
	t_hit		closest_hit;
	t_range		range;

	selected = NULL;
	closest_hit.t = DBL_MAX;
	object = scene->object;
	while (object != NULL)
	{
		range.min = 0.001;
		range.max = closest_hit.t;
		if (hit_object(object, ray, range, &hit))
		{
			closest_hit = hit;
			selected = object;
		}
		object = object->next;
	}
	return (selected);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_app	*app;
	t_ray	ray;

	app = (t_app *)param;
	if (app == NULL || app->scene == NULL || button != 1
		|| x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return (0);
	ray = shoot_ray(app->scene, x, y);
	app->selected_object = pick_object(app->scene, &ray);
	render_frame(app);
	return (0);
}
