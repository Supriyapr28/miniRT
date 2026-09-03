/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 12:00:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 12:05:00 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	make_shadow_ray(const t_hit *hit, const t_scene *scene)
{
	t_ray	shadow;
	t_vec3	to_light;

	shadow.origin = vec3_add(hit->point, vec3_scale(hit->normal, 0.001));
	to_light = vec3_sub(scene->light.origin, hit->point);
	shadow.direction = vec3_normalize(to_light);
	return (shadow);
}

double	color_ratio(int channel)
{
	if (channel <= 0)
		return (0.0);
	if (channel >= 255)
		return (1.0);
	return ((double)channel / 255.0);
}

int	clamp_channel(double value)
{
	if (value <= 0.0)
		return (0);
	if (value >= 255.0)
		return (255);
	return ((int)value);
}
