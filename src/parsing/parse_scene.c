/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 12:37:29 by spaipur-          #+#    #+#             */
/*   Updated: 2026/07/30 12:58:22 by uvadakku         ###   ########.fr       */
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
    
    scene->camera.coordinates.x = 0.0;
    scene->camera.coordinates.y = 0.0;
    scene->camera.coordinates.z = 0.0;
    scene->camera.direction.x = 0.0;
    scene->camera.direction.y = 0.0;
    scene->camera.direction.z = 0.0;
    scene->camera.fov = 0.0;
    scene->light.origin.x = 0.0;
    scene->light.origin.y = 0.0;
    scene->light.origin.z = 0.0;
    scene->light.brightness = 0.0;
    scene->light.color.r = 0;
    scene->light.color.g = 0;
    scene->light.color.b = 0;
    scene->object = NULL;
}

char *trim_line(t_scene *scene, char *line)
{
    char *trimmed;

    trimmed = ft_strtrim(line , "\t\r\n");
    free(line);
    if (!trimmed)
        ft_err_handler(scene, ERR_MEM_TRIM);
    return (trimmed);
}

int is_skippable_line(char *line)
{
    return (line[0] == '\0' || line[0] == '#');
}

static int validate_tokens(t_scene *scene, char **tokens)
{
    int    expected_count;
    size_t actual_count;

    // 1. Skip empty lines cleanly
    if (!tokens[0])
        return (0);
    // 2. Validate known element/object identifier
    expected_count = get_expected_token_count(tokens[0]);
    if (expected_count == 0)
        return (ft_err_handler(scene, ERR_UNKNOWN_OBJECT));
    // 3. Validate token count matches requirements
    actual_count = array_size(tokens);
    if (actual_count != (size_t)expected_count)
        return (ft_err_handler(scene, ERR_INVALID_TOKEN_COUNT));
    return (1);
}

int process_line(t_scene *scene, char *trimmed)
{
    char    **tokens;
    int     val_status;
    int     parse_status;

    tokens = create_tokens(scene, trimmed);
    if (!tokens)
        return (ft_err_handler(scene, ERR_MEM_TOKENIZATION));

    val_status = validate_tokens(scene, tokens);
    if (val_status <= 0)
    {
        free_tokens(tokens);
        if (val_status == 0)// 1 for empty line, error code otherwise
            return (1);
        return (val_status);
    }
    parse_status = dispatch_scene_parsing(scene, tokens);
    free_tokens(tokens);
    if (!parse_status)
        return (ft_err_handler(scene, ERR_INVALID_ELEMENT));
    return (1);
}

static int read_scene_file(int fd, t_scene *scene)
{
    char *line;
    char *trimmed;

    line = get_next_line(fd);
    while (line)
    {
        trimmed = trim_line(scene, line);
        if (!is_skippable_line(trimmed))
            process_line(scene, trimmed);
        free(trimmed);
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
        return (NULL);
    init_scene_defaults(scene);
    fd = open(scene_path, O_RDONLY);
    if (fd < 0)
    {
        ft_err_handler(scene, ERR_FILE_OPEN);
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


