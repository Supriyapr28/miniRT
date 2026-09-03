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

static void	init_scene_defaults(t_scene *scene)
{
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

static int	process_line(t_scene *scene, char *trimmed)
{
	char	**tokens;
	int		val_status;
	int		parse_status;

	tokens = create_tokens(scene, trimmed);
	if (tokens == NULL)
		return (-1);
	val_status = validate_tokens(scene, tokens);
	if (val_status == 0)
	{
		free_tokens(tokens);
		return (1);
	}
	if (val_status < 0)
	{
		free_tokens(tokens);
		return (-1);
	}
	parse_status = dispatch_scene_parsing(scene, tokens);
	free_tokens(tokens);
	if (parse_status < 0)
		return (-1);
	return (1);
}

static int	parse_file_line(t_scene *scene, char *line)
{
	char	*trimmed;
	int		status;

	trimmed = trim_line(scene, line);
	if (trimmed == NULL)
		return (-1);
	status = 1;
	if (is_skippable_line(trimmed) == 0)
		status = process_line(scene, trimmed);
	free(trimmed);
	return (status);
}

static int	read_scene_file(t_scene *scene, const char *path)
{
	int		fd;
	char	*line;
	int		fail;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_err_handler(scene, ERR_FILE_OPEN);
		return (0);
	}
	fail = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (fail == 0 && parse_file_line(scene, line) < 0)
			fail = 1;
		else if (fail == 1)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (fail == 0);
}

t_scene	*parse_scene(const char *scene_path)
{
	t_scene	*scene;

	scene = calloc(1, sizeof(*scene));
	if (scene == NULL)
		return (NULL);
	init_scene_defaults(scene);
	if (read_scene_file(scene, scene_path) == 0
		|| validate_scene(scene) == 0)
	{
		free_scene(scene);
		return (NULL);
	}
	ft_putstr_fd("Scene parsed successfully in ", 1);
	ft_putendl_fd((char *)scene_path, 1);
	return (scene);
}
