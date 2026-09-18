/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 12:00:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/18 10:16:07 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
