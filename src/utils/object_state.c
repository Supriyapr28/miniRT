/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 00:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/09/15 00:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	*object_get_position(t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (&obj->u_data.sphere.center);
	if (obj->type == OBJ_PLANE)
		return (&obj->u_data.plane.origin);
	if (obj->type == OBJ_CYLINDER)
		return (&obj->u_data.cylinder.origin);
	return (NULL);
}

static t_vec3	*get_axis(t_object *obj)
{
	if (obj->type == OBJ_PLANE)
		return (&obj->u_data.plane.normal);
	if (obj->type == OBJ_CYLINDER)
		return (&obj->u_data.cylinder.orientation);
	return (NULL);
}

void	object_save_initial(t_object *object)
{
	t_vec3	*pos;
	t_vec3	*axis;

	if (object == NULL)
		return ;
	pos = object_get_position(object);
	if (pos != NULL)
		object->initial_pos = *pos;
	axis = get_axis(object);
	if (axis != NULL)
		object->initial_axis = *axis;
}

void	object_restore_initial(t_object *object)
{
	t_vec3	*pos;
	t_vec3	*axis;

	if (object == NULL)
		return ;
	pos = object_get_position(object);
	if (pos != NULL)
		*pos = object->initial_pos;
	axis = get_axis(object);
	if (axis != NULL)
		*axis = object->initial_axis;
}
