/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array_ambient.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 11:40:43 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/27 11:41:21 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"

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