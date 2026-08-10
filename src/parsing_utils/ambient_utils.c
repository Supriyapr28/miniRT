/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 16:54:07 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/27 11:56:24 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "error.h"
// #include "parse.h"
// #include "objects.h"
// #include "rt.h"


// static const char	*handle_sign_and_space(const char *str, int *sign)
// {
// 	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
// 		str++;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			*sign = -1;
// 		str++;
// 	}
// 	return (str);
// }

// float	ft_atof(const char *str)
// {
// 	t_atof	p;

// 	p.fraction = 0.0f;
// 	p.divisor = 1.0f;
// 	p.sign = 1;

//     str = handle_sign_and_space(str, &p.sign);
// 	p.integer_part = (float)ft_atoi(str);
// 	while (*str >= '0' && *str <= '9')
// 		str++;
// 	if (*str == '.')
// 	{
// 		str++;
// 		while (*str >= '0' && *str <= '9')
// 		{
// 			p.fraction = p.fraction * 10.0f + (*str++ - '0');
// 			p.divisor *= 10.0f;
// 		}
// 	}
// 	return (p.sign * (p.integer_part + (p.fraction / p.divisor)));
// }


// int float_parser(char *str, float *out)
// {
//     int i;
//     int dot_count;

//     if (!str || !str[0])
//         return (1);
//     i = 0;
//     dot_count = 0;

//     if (str[i] == '+' || str[i] == '-')
//         i++;
//     while (str[i])
//     {
//         if (str[i] == '.')
//             dot_count++;
//         else if (str[i] < '0' || str[i] > '9')
//             return (1); //non digit character found
//         if (dot_count > 1)
//             return (1); // Multiple decimals like "0..5"
//         i++;
//     }
//     *out = ft_atof(str); //string to float
//     return (0);    
// }

