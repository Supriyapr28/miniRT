/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 15:20:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/09 15:20:00 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	reset_scene_state(t_app *app)
{
	t_object	*object;

	if (app == NULL || app->scene == NULL)
		return ;
	app->scene->camera = app->scene->initial_camera;
	object = app->scene->object;
	while (object != NULL)
	{
		object_restore_initial(object);
		object = object->next;
	}
	app->selected_object = NULL;
}
