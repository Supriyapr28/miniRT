/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 12:53:05 by spaipur-          #+#    #+#             */
/*   Updated: 2026/07/27 11:45:03 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int validate_ratio(float ratio)
{
    if (ratio < 0.0f || ratio > 1.0f)
        return (1);
    return (0);
}

void  validate_vector(t_vec3 vector)
{
    if (vector.x < -1.0 || vector.x > 1.0 || vector.y < -1.0 || vector.y > 1.0
        || vector.z < -1.0 || vector.z > 1.0)
        parse_error("Vector values must be in range -1.0 to 1.0");
}

void validate_color(t_color color)
{
    if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
        || color.b < 0 || color.b > 255)
        parse_error("Color values must be in range 0 to 255");
}

