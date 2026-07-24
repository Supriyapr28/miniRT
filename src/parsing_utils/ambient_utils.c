/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:03:07 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/23 17:38:32 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "error.h"
#include "parse.h"
#include "../libft/libft.h"

int validate_ratio(float ratio)
{
    if (ratio < 0.0f || ratio > 1.0f)
        return (1);
    return (0);
}

int float_parser(char *str, float *out)
{
    int i;
    int dot_count;

    if (!str || !str[0])
        return (1);
    i = 0;
    dot_count = 0;

    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (str[i] == '.')
            dot_count++;
        else if (str[i] < '0' || str[i] > '9')
            return (1); //non digit character found
        if (dot_count > 1)
            return (1); // Multiple decimals like "0..5"
        i++;
    }
    *out = ft_atof(str); //string to float
    return (0);    
}

size_t array_size(char **arr)
{
 size_t len;
 
 len = 0;
 if (!arr)
    return (0);
 while (arr[len])
    len++;
 return (len);
}

void free_array(char **arr)
{
    size_t i;
    
    if (!arr)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
