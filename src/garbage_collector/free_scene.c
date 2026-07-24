/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:00:00 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/20 18:08:33 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"

void free_scene(t_scene *scene)
{
	t_object	*current;
	t_object	*next;

	if (!scene)
		return ;
	current = scene->object;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	free(scene);
}
