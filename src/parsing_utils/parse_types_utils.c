/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 17:54:27 by uvadakku          #+#    #+#             */
/*   Updated: 2026/08/14 15:20:37 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	skip_spaces(const char *str, int i)
{
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	return (i);
}

static int	parse_integer_part(const char *str, int i, double *value)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		*value = *value * 10.0 + (str[i] - '0');
		i++;
	}
	return (i);
}

static int	parse_fractional_part(const char *str, int i, double *fraction,
	double *divisor)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		*fraction = *fraction * 10.0 + (str[i] - '0');
		*divisor *= 10.0;
		i++;
	}
	return (i);
}

int	parse_float(const char *str, double *out)
{
	int		i;
	int		sign;
	double	value;
	double	fraction;
	double	divisor;

	if (!str || !out || !*str)
		return (1);
	value = 0.0;
	fraction = 0.0;
	divisor = 1.0;
	sign = 1;
	i = skip_spaces(str, 0);
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	i = parse_integer_part(str, i, &value);
	if (str[i] == '.')
		i = parse_fractional_part(str, i + 1, &fraction, &divisor);
	i = skip_spaces(str, i);
	if (str[i] != '\0')
		return (1);
	*out = sign * (value + fraction / divisor);
	return (0);
}
