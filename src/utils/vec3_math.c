/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 12:22:11 by spaipur-          #+#    #+#             */
/*   Updated: 2026/08/04 11:27:33 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <float.h>

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return (result);
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return (result);
}

t_vec3 vec3_scale(t_vec3 a, double scalar)
{
    t_vec3 result;

    result.x = a.x * scalar;
    result.y = a.y * scalar;
    result.z = a.z * scalar;
    return (result);
}

double vec3_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return (result);
}