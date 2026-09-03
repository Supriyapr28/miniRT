/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 17:54:27 by uvadakku          #+#    #+#             */
/*   Updated: 2026/08/14 15:20:37 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#define BUFFER_SIZE 64

static int	skip_spaces(const char *str, int i)
{
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	return (i);
}

static int	parse_component(const char *str, int i, double *out)
{
	char	buffer[BUFFER_SIZE];
	int		j;
	int		k;

	j = 0;
	while (str[i] != ',' && str[i] != '\0')
	{
		if (j >= BUFFER_SIZE - 1)
			return (-1);
		buffer[j++] = str[i++];
	}
	buffer[j] = '\0';
	if (j == 0)
		return (-1);
	if (parse_float(buffer, out) != 0)
		return (-1);
	k = skip_spaces(str, i);
	if (str[k] != ',' && str[k] != '\0')
		return (-1);
	return (k);
}

int	parse_vector(const char *str, t_vec3 *out)
{
	int	i;

	if (!str || !out)
		return (1);
	i = parse_component(str, 0, &out->x);
	if (i < 0 || str[i] != ',')
		return (1);
	i++;
	i = parse_component(str, i, &out->y);
	if (i < 0 || str[i] != ',')
		return (1);
	i++;
	i = parse_component(str, i, &out->z);
	if (i < 0)
		return (1);
	i = skip_spaces(str, i);
	if (str[i] != '\0')
		return (1);
	return (0);
}

static int	parse_color_component(const char *str, int i, int *out)
{
	int	value;
	int	sign;
	int	has_digit;

	value = 0;
	sign = 1;
	has_digit = 0;
	i = skip_spaces(str, i);
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		has_digit = 1;
		value = value * 10 + (str[i] - '0');
		i++;
	}
	i = skip_spaces(str, i);
	if (!has_digit || (str[i] != ',' && str[i] != '\0'))
		return (-1);
	*out = sign * value;
	return (i);
}

int	parse_color(const char *str, t_color *out)
{
	int	i;

	if (!str || !out)
		return (1);
	i = parse_color_component(str, 0, &out->r);
	if (i < 0 || str[i] != ',')
		return (1);
	i++;
	i = parse_color_component(str, i, &out->g);
	if (i < 0 || str[i] != ',')
		return (1);
	i++;
	i = parse_color_component(str, i, &out->b);
	if (i < 0)
		return (1);
	i = skip_spaces(str, i);
	if (str[i] != '\0' || validate_color(*out) != 0)
		return (1);
	return (0);
}
