/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:42:48 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/30 12:25:33 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_MEM_TRIM \
	"Memory allocation failed during trimming a line"
# define ERR_MEM_TOKENIZATION    "Memory allocation failed during tokenization"
# define ERR_FILE_OPEN           "File doesn't exist or is not a valid file"
# define ERR_UNKNOWN_OBJECT      "Unknown object type"
# define ERR_INVALID_TOKEN_COUNT "Invalid token count for object"
# define ERR_INVALID_ELEMENT     "Invalid scene element"
# define ERR_UNKNOWN_IDENTIFIER  "Unknown identifier"
# define ERR_OVER_AMBIENTS       "Ambient already defined"
# define ERR_INVALID_PARAM       "Wrong number of tokens"
# define ERR_FLOAT               "Invalid float"
# define ERR_AMBIENT_RATIO       "Ambient ratio must be 0.0 - 1.0"
# define ERR_INVALID_COLOR       "Invalid RGB color"
# define ERR_OVER_CAMERA         "Camera already defined"
# define ERR_CAMERA_PARAM        "Wrong number of tokens"
# define ERR_INVALID_COORD       "Invalid coordinate"
# define ERR_INVALID_DIRECT      "Invalid direction"
# define ERR_VECTOR_RANGE        "Vector out of range"
# define ERR_FOV_RANGE           "FOV must be within valid range (0-180)"
# define ERR_LIGHT_PARAM         "Wrong number of tokens"
# define ERR_LIGHT_BRIGHTNESS    "Light brightness must be 0.0 - 1.0"
# define ERR_INVALID_ORIENT      "invalid orientation"
# define ERR_MALLOC              "Malloc error"

#endif
