/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:28:29 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/30 12:25:46 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "error.h"
#include "parse.h"
#include "../libft/libft.h"

int parse_light(t_scene *scene, char **tokens)
{
 // or your project's memory error code
    if (parse_vector(tokens[1], &scene->light.origin))
        return ft_err_handler(scene, ERR_INVALID_COORD);
    if (parse_float(tokens[2], &scene->light.brightness))
        return ft_err_handler(scene, ERR_FLOAT);
    if (validate_ratio(scene->light.brightness))
        return ft_err_handler(scene, ERR_LIGHT_BRIGHTNESS);
    if (parse_color(tokens[3], &scene->light.color))
        return ft_err_handler(scene, ERR_INVALID_COLOR);
    return (1);
}

int parse_camera(t_scene *scene, char **tokens)
{
    if (scene->camera.is_set)
        return ft_err_handler(scene, ERR_OVER_CAMERA);
    if (parse_vector(tokens[1], &scene->camera.coordinates))
        return ft_err_handler(scene, ERR_INVALID_COORD);
    if (parse_vector(tokens[2], &scene->camera.direction))
        return ft_err_handler(scene, ERR_INVALID_DIRECT);
    // orientation must be normalized
    if (validate_normalized_vector(scene->camera.direction))
        return ft_err_handler(scene, ERR_VECTOR_RANGE);
    // 5.parse the field of view
    if (parse_float(tokens[3], &scene->camera.fov))
        return ft_err_handler(scene, ERR_FLOAT);
    //FOv must be within vallid range (0-180)
    if (validate_fov(scene->camera.fov))
        return ft_err_handler(scene, ERR_FOV_RANGE);
    //Mark camera as set and store type
    scene->camera.id = OBJ_CAMERA;
    scene->camera.is_set = 1;

    return (1);
} 

int parse_ambient(t_scene *scene, char **tokens)
{
    double   ratio;
    t_color color;

    // 1. Check duplicate ambient
    if (scene->ambient.is_set)
        return ft_err_handler(scene, ERR_OVER_AMBIENTS);
    if (parse_float(tokens[1], &ratio))
        return ft_err_handler(scene, ERR_AMBIENT_RATIO);
    if (validate_ratio(ratio))
        return ft_err_handler(scene, ERR_AMBIENT_RATIO);
    // 4. Parse color --> not done
    if (parse_color(tokens[2], &color))
        return ft_err_handler(scene, ERR_INVALID_COLOR);
    // 5. Store into scene
    scene->ambient.id = OBJ_AMBIENT;
    scene->ambient.is_set = 1;
    scene->ambient.ratio = ratio;
    scene->ambient.color = color;
    return (1);
}

int  dispatch_scene_parsing(t_scene *scene, char **tokens)
{
	char *type;

	type = tokens[0];
	if(ft_strncmp(type, "A", 2) == 0)
		return (parse_ambient(scene, tokens));
	if(ft_strncmp(type, "C", 2) == 0)
		return (parse_camera(scene, tokens));
	if(ft_strncmp(type, "L", 2) == 0)
		return (parse_light(scene, tokens));
	if(ft_strncmp(type, "sp", 3) == 0)
		return (parse_sphere(scene, tokens));
	if(ft_strncmp(type, "pl", 3) == 0)
		return (parse_plane(scene, tokens));
	if(ft_strncmp(type, "cy", 3) == 0)
		return (parse_cylinder(scene, tokens));
	return ft_err_handler(scene, ERR_UNKNOWN_IDENTIFIER);
}

