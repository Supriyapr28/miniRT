/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 12:19:41 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 12:00:00 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <float.h>

bool	intersect_spheres(const t_scene *scene, const t_ray *ray,
			t_hit *closest_hit)
{
	t_object	*current;
	t_hit		temp_hit;
	bool		hit_anything;
	t_range		range;

	current = scene->object;
	hit_anything = false;
	while (current != NULL)
	{
		if (current->type == OBJ_SPHERE)
		{
			range.min = 0.001;
			range.max = closest_hit->t;
			if (hit_sphere(&current->u_data.sphere, ray, range, &temp_hit))
			{
				*closest_hit = temp_hit;
				hit_anything = true;
			}
		}
		current = current->next;
	}
	return (hit_anything);
}

bool	trace_ray(const t_scene *scene, const t_ray *ray,
			t_hit *closest_hit)
{
	bool	hit_anything;

	closest_hit->t = DBL_MAX;
	hit_anything = false;
	hit_anything |= intersect_spheres(scene, ray, closest_hit);
	hit_anything |= intersect_planes(scene, ray, closest_hit);
	hit_anything |= intersect_cylinder(scene, ray, closest_hit);
	return (hit_anything);
}

void	render_scene(const t_scene *scene, t_image *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			render_pixel(scene, img, x, y);
			x++;
		}
		y++;
	}
}
