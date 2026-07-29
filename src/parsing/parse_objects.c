/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 11:21:36 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/28 20:01:04 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int parse_sphere(t_scene *scene, char **tokens)
{
	t_object *obj = add_object(scene, OBJ_SPHERE); // however you allocate objects

	if (parse_vector(tokens[1], &obj->u.sphere.center))
		return ft_err_handler(scene, ERR_INVALID_COORD);

	if (parse_float(tokens[2], &obj->u.sphere.diameter))
		return ft_err_handler(scene, ERR_FLOAT);

	if (parse_color(tokens[3], &obj->u.sphere.color))
		return ft_err_handler(scene, ERR_INVALID_COLOR);

	return (1);
}

int parse_plane(t_scene *scene, char **tokens)
{
	t_object *obj = add_object(scene, OBJ_PLANE);
	
	if (parse_vector(tokens[1], &obj->u.plane.origin))
		return ft_err_handler(scene, ERR_INVALID_COORD);

	if (parse_vector(tokens[2], &obj->u.plane.normal))
		return ft_err_handler(scene, ERR_INVALID_DIRECT);

	if (validate_normalized_vector(obj->u.plane.normal))
		return ft_err_handler(scene, ERR_VECTOR_RANGE);

	if (parse_color(tokens[3], &obj->u.plane.color))
		return ft_err_handler(scene, ERR_INVALID_COLOR);

	return (1);
}

int parse_cylinder(t_scene *scene, char **tokens)
{
	t_object *obj = add_object(scene, OBJ_CYLINDER);

	if (parse_vector(tokens[1], &obj->u.cylinder.origin))
		return ft_err_handler(scene, ERR_INVALID_COORD);

	if (parse_vector(tokens[2], &obj->u.cylinder.orientation))
		return ft_err_handler(scene, ERR_INVALID_ORIENT);

	if (validate_normalized_vector(obj->u.cylinder.orientation))
		return ft_err_handler(scene, ERR_VECTOR_RANGE);

	if (parse_float(tokens[3], &obj->u.cylinder.diameter))
		return ft_err_handler(scene, ERR_FLOAT);

	if (parse_float(tokens[4], &obj->u.cylinder.height))
		return ft_err_handler(scene, ERR_FLOAT);

	if (parse_color(tokens[5], &obj->u.cylinder.color))
		return ft_err_handler(scene, ERR_INVALID_COLOR);
		
	return (1);
}
