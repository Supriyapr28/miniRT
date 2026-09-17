/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:03:57 by uvadakku          #+#    #+#             */
/*   Updated: 2026/09/14 17:03:34 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(*mlx));
	if (mlx == NULL)
		return (NULL);
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		free(mlx);
		return (NULL);
	}
	mlx->win = NULL;
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->bpp = 0;
	mlx->line_len = 0;
	mlx->endian = 0;
	return (mlx);
}

void	setup_hooks(t_app *app)
{
	mlx_hook(app->mlx->win, 2, 1L << 0, handle_key, app);
	mlx_mouse_hook(app->mlx->win, handle_mouse, app);
	mlx_hook(app->mlx->win, 17, 0, handle_close, app);
}

static int	create_image(t_mlx *mlx)
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
	render_scene(app);
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
