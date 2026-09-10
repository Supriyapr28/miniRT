/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:03:57 by uvadakku          #+#    #+#             */
/*   Updated: 2026/09/10 14:54:08 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	create_image(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (mlx->img == NULL)
	{
		printf("failed to create an image\n");
		destroy_mlx(mlx);
		return (0);
	}
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_len, &mlx->endian);
	return (1);
}

t_mlx	*start_mlx(t_app *app)
{
	t_mlx	*mlx;

	mlx = init_mlx();
	if (mlx == NULL)
	{
		printf("failed to initialize the connection with minilibx\n");
		return (NULL);
	}
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (mlx->win == NULL)
	{
		printf("failed to create the window\n");
		destroy_mlx(mlx);
		return (NULL);
	}
	if (create_image(mlx) == 0)
		return (NULL);
	app->mlx = mlx;
	render_frame(app);
	return (mlx);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
	{
		printf("usage: ./miniRT scenes/scene.rt\n");
		return (1);
	}
	app.mlx = NULL;
	app.scene = parse_scene(argv[1]);
	if (app.scene == NULL)
		return (1);
	app.selected_object = NULL;
	if (start_mlx(&app) == NULL)
	{
		free_scene(app.scene);
		return (1);
	}
	setup_hooks(&app);
	mlx_loop(app.mlx->mlx);
	destroy_app(&app);
	return (0);
}
