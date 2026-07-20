/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 12:41:32 by spaipur-          #+#    #+#             */
/*   Updated: 2026/07/20 13:21:22 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void free_tokens(char **tokens)
{
    int i;

    if (!tokens)
        return ;
    i = 0;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}