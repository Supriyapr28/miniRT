/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:28:29 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/27 12:03:45 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "error.h"
#include "parse.h"
#include "../libft/libft.h"

int parse_ambient(t_scene *scene, char **tokens)
{
    double   ratio;
    t_color color;

    // 1. Check duplicate ambient
    if (scene->ambient.is_set)
        return ft_err_handler(scene, ERR_OVER_AMBIENTS);
    // 2. Token count must be exactly 3: A ratio color
    if (array_size(tokens) != 3) 
        return ft_err_handler(scene, ERR_INVALID_PARAM);
    // 3. Parse ratio
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
	return (0);
}


