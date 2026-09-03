/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pl_cyl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:54:17 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 12:00:00 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	intersect_planes(const t_scene *scene, const t_ray *ray,
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
		if (current->type == OBJ_PLANE)
		{
			range.min = 0.001;
			range.max = closest_hit->t;
			if (hit_plane(&current->u_data.plane, ray, range, &temp_hit))
			{
				*closest_hit = temp_hit;
				hit_anything = true;
			}
		}
		current = current->next;
	}
	return (hit_anything);
}

bool	intersect_cylinder(const t_scene *scene, const t_ray *ray,
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
		if (current->type == OBJ_CYLINDER)
		{
			range.min = 0.001;
			range.max = closest_hit->t;
			if (hit_cylinder(&current->u_data.cylinder, ray, range, &temp_hit))
			{
				*closest_hit = temp_hit;
				hit_anything = true;
			}
		}
		current = current->next;
	}
	return (hit_anything);
}
