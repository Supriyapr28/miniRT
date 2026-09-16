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

void	object_translate(t_object *object, t_vec3 delta)
{
	if (object == NULL)
		return ;
	if (object->type == OBJ_SPHERE)
		object->u_data.sphere.center = vec3_add
			(object->u_data.sphere.center, delta);
	else if (object->type == OBJ_PLANE)
		object->u_data.plane.origin = vec3_add
			(object->u_data.plane.origin, delta);
	else if (object->type == OBJ_CYLINDER)
		object->u_data.cylinder.origin = vec3_add
			(object->u_data.cylinder.origin, delta);
}

void	object_rotate(t_object *object, t_vec3 axis, double angle)
{
	if (object == NULL)
		return ;
	if (object->type == OBJ_PLANE)
		object->u_data.plane.normal = vec3_normalize
			(rotate_vector(object->u_data.plane.normal, axis, angle));
	else if (object->type == OBJ_CYLINDER)
		object->u_data.cylinder.orientation = vec3_normalize
			(rotate_vector(object->u_data.cylinder.orientation, axis, angle));
}

void	object_save_initial(t_object *object)
{
	if (object == NULL)
		return ;
	if (object->type == OBJ_SPHERE)
		object->initial_pos = object->u_data.sphere.center;
	else if (object->type == OBJ_PLANE)
	{
		object->initial_pos = object->u_data.plane.origin;
		object->initial_axis = object->u_data.plane.normal;
	}
	else if (object->type == OBJ_CYLINDER)
	{
		object->initial_pos = object->u_data.cylinder.origin;
		object->initial_axis = object->u_data.cylinder.orientation;
	}
}

void	object_restore_initial(t_object *object)
{
	if (object == NULL)
		return ;
	if (object->type == OBJ_SPHERE)
		object->u_data.sphere.center = object->initial_pos;
	else if (object->type == OBJ_PLANE)
	{
		object->u_data.plane.origin = object->initial_pos;
		object->u_data.plane.normal = object->initial_axis;
	}
	else if (object->type == OBJ_CYLINDER)
	{
		object->u_data.cylinder.origin = object->initial_pos;
		object->u_data.cylinder.orientation = object->initial_axis;
	}
}
