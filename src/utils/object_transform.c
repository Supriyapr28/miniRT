/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:20:00 by uvadakku          #+#    #+#             */
/*   Updated: 2026/09/10 10:50:30 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static t_vec3	rotate_vector(t_vec3 vector, t_vec3 axis, double angle)
{
	t_vec3	parallel;
	t_vec3	perpendicular;
	t_vec3	cross;

	axis = vec3_normalize(axis);
	parallel = vec3_scale(axis, vec3_dot(axis, vector));
	perpendicular = vec3_sub(vector, parallel);
	cross = vec3_cross(axis, vector);
	return (vec3_add(parallel, vec3_add
			(vec3_scale(perpendicular, cos(angle)),
				vec3_scale(cross, sin(angle)))));
}

static t_vec3	*get_axis(t_object *obj)
{
	if (obj->type == OBJ_PLANE)
		return (&obj->u_data.plane.normal);
	if (obj->type == OBJ_CYLINDER)
		return (&obj->u_data.cylinder.orientation);
	return (NULL);
}

void	object_translate(t_object *object, t_vec3 delta)
{
	t_vec3	*pos;

	if (object == NULL)
		return ;
	pos = object_get_position(object);
	if (pos != NULL)
		*pos = vec3_add(*pos, delta);
}

void	object_rotate(t_object *object, t_vec3 axis, double angle)
{
	t_vec3	*obj_axis;

	if (object == NULL)
		return ;
	obj_axis = get_axis(object);
	if (obj_axis != NULL)
		*obj_axis = vec3_normalize(rotate_vector(*obj_axis, axis, angle));
}
