/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 11:21:36 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/31 14:41:58 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>

t_object	*add_object(t_scene *scene, t_obj_type type)
{
	t_object	*new_obj;
	t_object	*current;

	new_obj = malloc(sizeof(t_object));
	if (!new_obj)
		return (NULL);
	new_obj->type = type;
	new_obj->material = (t_color){0, 0, 0};
	new_obj->next = NULL;
	if (!scene->object)
		scene->object = new_obj;
	else
	{
		current = scene->object;
		while (current->next)
			current = current->next;
		current->next = new_obj;
	}
	return (new_obj);
}

static int	parse_size(t_scene *scene, char *token, double *value,
		const char *msg)
{
	if (parse_float(token, value))
		return (ft_err_handler(scene, ERR_FLOAT));
	if (*value <= 0.0)
		return (ft_err_handler(scene, msg));
	return (1);
}

int	parse_sphere(t_scene *scene, char **tokens)
{
	t_object	*obj;
	double		diameter;

	obj = add_object(scene, OBJ_SPHERE);
	if (!obj)
		return (ft_err_handler(scene, ERR_MALLOC));
	if (parse_vector(tokens[1], &obj->u_data.sphere.center))
		return (ft_err_handler(scene, ERR_INVALID_COORD));
	if (parse_size(scene, tokens[2], &diameter, ERR_DIAMETER) < 0)
		return (-1);
	obj->u_data.sphere.radius = diameter / 2.0;
	if (parse_color(tokens[3], &obj->u_data.sphere.color))
		return (ft_err_handler(scene, ERR_INVALID_COLOR));
	obj->material = obj->u_data.sphere.color;
	return (1);
}

int	parse_plane(t_scene *scene, char **tokens)
{
	t_object	*obj;

	obj = add_object(scene, OBJ_PLANE);
	if (!obj)
		return (ft_err_handler(scene, ERR_MALLOC));
	if (parse_vector(tokens[1], &obj->u_data.plane.origin))
		return (ft_err_handler(scene, ERR_INVALID_COORD));
	if (parse_vector(tokens[2], &obj->u_data.plane.normal))
		return (ft_err_handler(scene, ERR_INVALID_DIRECT));
	if (validate_normalized_vector(obj->u_data.plane.normal))
		return (ft_err_handler(scene, ERR_VECTOR_RANGE));
	if (parse_color(tokens[3], &obj->u_data.plane.color))
		return (ft_err_handler(scene, ERR_INVALID_COLOR));
	obj->material = obj->u_data.plane.color;
	return (1);
}

int	parse_cylinder(t_scene *scene, char **tokens)
{
	t_object	*obj;
	double		diameter;
	double		height;

	obj = add_object(scene, OBJ_CYLINDER);
	if (!obj)
		return (ft_err_handler(scene, ERR_MALLOC));
	if (parse_vector(tokens[1], &obj->u_data.cylinder.origin))
		return (ft_err_handler(scene, ERR_INVALID_COORD));
	if (parse_vector(tokens[2], &obj->u_data.cylinder.orientation))
		return (ft_err_handler(scene, ERR_INVALID_ORIENT));
	if (validate_normalized_vector(obj->u_data.cylinder.orientation))
		return (ft_err_handler(scene, ERR_VECTOR_RANGE));
	if (parse_size(scene, tokens[3], &diameter, ERR_DIAMETER) < 0)
		return (-1);
	obj->u_data.cylinder.radius = diameter / 2.0;
	if (parse_size(scene, tokens[4], &height, ERR_HEIGHT) < 0)
		return (-1);
	obj->u_data.cylinder.half_height = height / 2.0;
	if (parse_color(tokens[5], &obj->u_data.cylinder.color))
		return (ft_err_handler(scene, ERR_INVALID_COLOR));
	obj->material = obj->u_data.cylinder.color;
	return (1);
}
