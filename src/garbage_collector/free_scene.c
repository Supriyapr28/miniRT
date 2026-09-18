/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:00:00 by uvadakku          #+#    #+#             */
/*   Updated: 2026/09/18 10:44:57 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "rt.h"

void	free_tokens(char **tokens)
{
	int	i;

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

void	free_scene(t_scene *scene)
{
	t_object	*current;
	t_object	*next;

	if (!scene)
		return ;
	current = scene->object;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(scene);
}
