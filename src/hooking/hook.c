/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:10:59 by uvadakku          #+#    #+#             */
/*   Updated: 2026/09/01 18:11:40 by us               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	setup_hooks(t_app *app)
{
	mlx_hook(app->mlx->win, 2, 1L << 0, handle_key, app);
	mlx_hook(app->mlx->win, 17, 0, handle_close, app);
}

void	destroy_app(t_app *app)
{
	if (app == NULL)
		return ;
	if (app->scene != NULL)
		free_scene(app->scene);
	destroy_mlx(app->mlx);
}
