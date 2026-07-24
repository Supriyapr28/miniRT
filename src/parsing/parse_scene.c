/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 12:37:29 by spaipur-          #+#    #+#             */
/*   Updated: 2026/07/24 14:21:46 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "objects.h"
#include <fcntl.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"

static void init_scene_defaults(t_scene *scene)
{
      // Ambient
    scene->ambient.id = 0;
    scene->ambient.is_set = 0;
    scene->ambient.ratio = 0.0;
    scene->ambient.color.r = 0;
    scene->ambient.color.g = 0;
    scene->ambient.color.b = 0;
    
    scene->camera.origin.x = 0.0;
    scene->camera.origin.y = 0.0;
    scene->camera.origin.z = 0.0;
    scene->camera.direction.x = 0.0;
    scene->camera.direction.y = 0.0;
    scene->camera.direction.z = 0.0;
    scene->camera.fov = 0.0;
    scene->light.origin.x = 0.0;
    scene->light.origin.y = 0.0;
    scene->light.origin.z = 0.0;
    scene->light.brightness = 0.0;
    scene->light.color = 0;
    scene->object = NULL;
}

char *trim_line(char *line)
{
    char *trimmed;
    trimmed = ft_strtrim(line , "\t\r\n");
    if (!trimmed)
        parse_error("Memory allocation failed during trimming a line");
    return (trimmed);
}

int is_skippable_line(char *line)
{
    return (line[0] == '\0' || line[0] == '#');
}

int process_line(t_scene *scene, char *trimmed)
{
    char **tokens;

    tokens = create_tokens(trimmed);
    if (!tokens)
        return (0);
    if (!validate_token(tokens))
    {
        free_tokens(tokens);
        return (0);
    }
    if (!dispatch_scene_parsing(scene, tokens)) /* maps identifier to parse_* */
    {
        free_tokens(tokens);
        return (0);
    }
    free_tokens(tokens);
    return (1);
}

static int read_scene_file(int fd, t_scene *scene)
{
    char *line;
    char *trimmed;

    line = get_next_line(fd);
    while (line)
    {
        trimmed = trim_line(line);
        if (!is_skippable_line(trimmed))
        {
            if (!process_line(scene, trimmed))
            {
               // free(trimmed);
                return (0); // Return failure
            }
        }
       // free(trimmed);
        line = get_next_line(fd);
    }
    return (1); // Return success
}

t_scene *parse_scene(const char *scene_path)
{
    int      fd;
    t_scene *scene;

    scene = calloc(1, sizeof(*scene));
    if (!scene)
        return (NULL); // Fixed: changed from 1 to NULL
    init_scene_defaults(scene);
    fd = open(scene_path, O_RDONLY);
    if (fd < 0)
    {
        parse_error("file doesnt exist or is not a valid file");
        free(scene);
        return (NULL);
    }
    if (!read_scene_file(fd, scene))
    {
        close(fd);
        free_scene(scene);
        return (NULL);
    }
    close(fd);
    ft_putstr_fd("Scene parsed successfully in ", 1);
    ft_putendl_fd((char *)scene_path, 1);
    return (scene);
}


