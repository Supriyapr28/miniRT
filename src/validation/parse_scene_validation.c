/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 12:53:05 by spaipur-          #+#    #+#             */
/*   Updated: 2026/08/25 16:36:11 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	validate_tokens(t_scene *scene, char **tokens)
{
	int		expected_count;
	size_t	actual_count;

	if (!tokens[0])
		return (0);
	expected_count = get_expected_token_count(tokens[0]);
	if (expected_count == 0)
		return (ft_err_handler(scene, ERR_UNKNOWN_OBJECT));
	actual_count = array_size(tokens);
	if (actual_count != (size_t)expected_count)
		return (ft_err_handler(scene, ERR_INVALID_TOKEN_COUNT));
	return (1);
}

int	validate_scene(t_scene *scene)
{
	if (scene->ambient.is_set == 0)
	{
		ft_err_handler(scene, ERR_MISSING_AMBIENT);
		return (0);
	}
	if (scene->camera.is_set == 0)
	{
		ft_err_handler(scene, ERR_MISSING_CAMERA);
		return (0);
	}
	return (1);
}
