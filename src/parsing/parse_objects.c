/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 11:21:36 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/30 11:40:52 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>

t_object *add_object(t_scene *scene, t_obj_type type)
{
	t_object *new_obj;
	t_object *current;

	new_obj = malloc(sizeof(t_object)); //Allocate memory for new_obj
	if(!new_obj)
		return (NULL);
	new_obj->type = type; //Initialize node properties
	new_obj->next = NULL; 
	
	if (!scene->object) //Attach to scene object linked list
	{
		scene->object = new_obj;
	}
	else
	{
		current = scene->object;
		while (current->next)
			current = current->next;
		current->next = new_obj;
	}
	return (new_obj);
}

int parse_sphere(t_scene *scene, char **tokens)
{
	t_object *obj = add_object(scene, OBJ_SPHERE); // however you allocate objects
	if (!obj)
        return (ft_err_handler(scene, ERR_MALLOC));
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
	if (!obj)
		return (ft_err_handler(scene, ERR_MALLOC));
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
	if (!obj)
        return (ft_err_handler(scene, ERR_MALLOC));
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
