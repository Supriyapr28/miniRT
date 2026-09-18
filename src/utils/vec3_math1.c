/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_math1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 12:25:18 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/18 10:49:14 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <float.h>
#include <math.h>
#include "rt.h"

bool	solve_quadratic(const t_quad_params *params, double *t)
{
	double	discriminant;
	double	sqrt_d;

	discriminant = params->b * params->b - 4.0 * params->a * params->c;
	if (discriminant < 0.0)
		return (false);
	sqrt_d = sqrt(discriminant);
	*t = (-params->b - sqrt_d) / (2.0 * params->a);
	if (*t < params->range.min || *t > params->range.max)
	{
		*t = (-params->b + sqrt_d) / (2.0 * params->a);
		if (*t < params->range.min || *t > params->range.max)
			return (false);
	}
	return (true);
}

double	vec3_abs(double value)
{
	if (value < 0.0)
		return (-value);
	return (value);
}

static double	vec3_sqrt(double value)
{
	double	guess;
	double	next;
	int		i;

	if (value <= 0.0)
		return (0.0);
	guess = value;
	i = 0;
	while (i < 20)
	{
		next = 0.5 * (guess + value / guess);
		if (vec3_abs(next - guess) < 1e-12)
			return (next);
		guess = next;
		i++;
	}
	return (guess);
}

double	vec3_length(t_vec3 a)
{
	return (vec3_sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double	length;
	t_vec3	result;

	length = vec3_length(a);
	if (vec3_abs(length) < 1e-12)
		return ((t_vec3){0.0, 0.0, 0.0});
	result.x = a.x / length;
	result.y = a.y / length;
	result.z = a.z / length;
	return (result);
}
