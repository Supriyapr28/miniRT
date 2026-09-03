/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 17:16:42 by us                #+#    #+#             */
/*   Updated: 2026/09/01 17:27:25 by us               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_image	image_from_mlx(t_mlx *mlx)
{
	t_image	image;

	image.width = WIN_WIDTH;
	image.height = WIN_HEIGHT;
	image.bpp = mlx->bpp;
	image.line_length = mlx->line_len;
	image.endian = mlx->endian;
	image.mlx_img = mlx->img;
	image.addr = mlx->addr;
	image.pixels = NULL;
	return (image);
}

void	render_frame(t_app *app)
{
	t_image	image;

	if (app == NULL || app->mlx == NULL || app->scene == NULL)
		return ;
	image = image_from_mlx(app->mlx);
	render_scene(app->scene, &image);
	mlx_put_image_to_window(app->mlx->mlx, app->mlx->win,
		app->mlx->img, 0, 0);
}
