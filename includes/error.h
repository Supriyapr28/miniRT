/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:42:48 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/21 16:19:16 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../includes/objects.h"
# include "../includes/parse.h"

//elements
#define ERR_OVER_AMBIENTS  "Ambient already defined"
#define ERR_INVALID_PARAM       "Wrong number of tokens"
#define ERR_FLOAT          "Invalid float"
#define ERR_AMBIENT_RATIO         "Ambient ratio must be 0.0 - 1.0"
#define ERR_INVALID_COLOR         "Invalid RGB color"

#endif