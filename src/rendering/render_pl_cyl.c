/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pl_cyl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:54:17 by uvadakku          #+#    #+#             */
/*   Updated: 2026/08/17 16:25:48 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "rt.h"
#include "objects.h"
#include "float.h"

bool intersect_planes(const t_scene *scene, const t_ray *ray, t_hit *closest_hit)
{
	t_object	*current;
	t_hit temp_hit;
	bool hit_anything = false;
	
	current = scene->object;
	while (current != NULL)
	{
		if (current->type == OBJ_PLANE  
			&& hit_plane(&current->u.plane, ray,
				0.001f, (float)closest_hit->t, &temp_hit))
		{
			*closest_hit = temp_hit;
			hit_anything = true;
		}
		current = current->next;
	}
	return (hit_anything);
}


bool intersect_cylinder(const t_scene *scene, const t_ray *ray, t_hit *closest_hit)
{
	t_object	*current;
	t_hit temp_hit;
	bool hit_anything = false;
	
	current = scene->object;
	while (current != NULL)
	{
		if (current->type == OBJ_CYLINDER
			&& hit_cylinder(&current->u.cylinder, ray,
				0.001f, (float)closest_hit->t, &temp_hit))
		{
			*closest_hit = temp_hit;
			hit_anything = true;
		}
		current = current->next;
	}
	return (hit_anything);
}
