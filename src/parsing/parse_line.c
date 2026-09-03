/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:18:20 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 14:18:22 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parse.h"

int	get_expected_token_count(char *type)
{
	if (ft_strncmp(type, "A", 2) == 0)
		return (3);
	if (ft_strncmp(type, "C", 2) == 0)
		return (4);
	if (ft_strncmp(type, "L", 2) == 0)
		return (4);
	if (ft_strncmp(type, "sp", 3) == 0)
		return (4);
	if (ft_strncmp(type, "pl", 3) == 0)
		return (4);
	if (ft_strncmp(type, "cy", 3) == 0)
		return (6);
	return (0);
}

char	*trim_line(t_scene *scene, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, "\t\r\n");
	free(line);
	if (!trimmed)
		ft_err_handler(scene, ERR_MEM_TRIM);
	return (trimmed);
}

int	is_skippable_line(char *line)
{
	return (line[0] == '\0' || line[0] == '#');
}

char	**create_tokens(t_scene *scene, char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens)
		ft_err_handler(scene, ERR_MEM_TOKENIZATION);
	return (tokens);
}
