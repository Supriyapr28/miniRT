/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 17:54:27 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/24 15:15:16 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h" 
#include "objects.h"

#define BUFFER_SIZE 64

static int skip_spaces(const char *str, int i)
{
    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
        i++;
    return (i);
}

static int parse_integer_part(const char *str, int i, double *value)
{
    while (str[i] >= '0' && str[i] <= '9')
    {
        *value = *value * 10.0 + (str[i] - '0');
        i++;
    }
    return (i);
}

static int parse_fractional_part(const char *str, int i, double *fraction,
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
 
int parse_camera(t_scene *scene, char **tokens) 
{ 
    (void)scene; 
    (void)tokens; 
    return (1); 
} 

int parse_light(t_scene *scene, char **tokens) 
{ 
    (void)scene; 
    (void)tokens; 
    return (1); 
} 

int parse_sphere(t_scene *scene, char **tokens) 

{ 
    (void)scene; 
    (void)tokens; 
    return (1); 
} 

int parse_plane(t_scene *scene, char **tostatic int parse_component(const char *str, int i, double *out)kens) 
{ 

    (void)scene; 
    (void)tokens; 
    return (1); 
} 

int parse_cylinder(t_scene *scene, char **tokens) 

{ 
    (void)scene; 
    (void)tokens; 
    return (1); 
} 

int parse_float(const char *str, double *out)
{
    int i;
    int sign;
    double value;
    double fraction;
    double divisor;

    if (!str || !out || !*str)
        return (1);
    i = 0;
    sign = 1;
    value = 0.0;
    fraction = 0.0;
    divisor = 1.0;
    i = skip_spaces(str, i);
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    i = parse_integer_part(str, i, &value);
    if (str[i] == '.')
    {
        i++;
        i = parse_fractional_part(str, i, &fraction, &divisor);
    }
    i = skip_spaces(str, i);
    if (str[i] != '\0')
        return (1);
    *out = sign * (value + fraction / divisor);
    return (0);
}

static int parse_component(const char *str, int i, double *out)
{
    char buffer[BUFFER_SIZE];
    int j;
    int k;

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

int parse_vector(const char *str, t_vec3 *out)
{
    int i;

    if (!str || !out)
        return (1);
    i = 0;
    i = parse_component(str, i, &out->x);
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

static int parse_color_component(const char *str, int i, int *out)
{
    int value;
    int sign;

    value = 0;
    sign = 1;
    i = skip_spaces(str, i);
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        value = value * 10 + (str[i] - '0');
        i++;
    }
    i = skip_spaces(str, i);
    if (str[i] != ',' && str[i] != '\0')
        return (-1);
    *out = sign * value;
    return (i);
}

int parse_color(const char *str, t_color *out)
{
    int i;

    if (!str || !out)
        return (1);
    i = 0;
    i = parse_color_component(str, i, &out->r);
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
    if (str[i] != '\0')
        return (1);
    return (0);
}
