/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 12:37:29 by spaipur-          #+#    #+#             */
/*   Updated: 2026/07/20 12:39:45 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <fcntl.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"

char *trim_line(char *line)
{
    char *trimmed;
    trimmed = ft_strtrim(line , "\t\r\n");
    free(line);
    if (!trimmed)
        parse_error("Memory allocation failed during trimming a line");
    return (trimmed);
}

int is_skippable_line(char *line)
{
    return (line[0] == '\0' || line[0] == '#');
}

void parse_scene(char *scene_path)
{
    int fd;
    char *line;
    char *trimmed;
    char **tokens;

    fd = open(scene_path, O_RDONLY);
    if (fd < 0)
        parse_error("file doesnt exist or is not a valid file");
    line = get_next_line(fd);
    while(line)
    {
        trimmed = trim_line(line);
        if(!is_skippable_line(trimmed))
        {
            tokens = create_tokens(trimmed);
            validate_token(tokens);
            free_tokens(tokens);
        }
        line = get_next_line(fd);
    }
    close(fd);
    ft_putstr_fd("Scene parsed successfully in ", 1);
    ft_putendl_fd(scene_path, 1);
}

