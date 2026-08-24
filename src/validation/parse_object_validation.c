/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 12:53:05 by spaipur-          #+#    #+#             */
/*   Updated: 2026/08/20 14:16:23 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int validate_fov(double fov)
{
	if (fov <= 0.0 || fov >= 180.0)
		return (1);
	return (0);
}

int validate_ratio(float ratio)
{
	if (ratio < 0.0f || ratio > 1.0f)
		return (1);
	return (0);
}

int validate_normalized_vector(t_vec3 vector)
{
	if (vector.x < -1.0 || vector.x > 1.0 || vector.y < -1.0 || vector.y > 1.0
		|| vector.z < -1.0 || vector.z > 1.0)
		return (1);
	if (vector.x == 0.0 && vector.y == 0.0 && vector.z == 0.0)
		return (1);
	return (0);
}

int validate_color(t_color color)
{
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
		return (1);
	return (0);
}

