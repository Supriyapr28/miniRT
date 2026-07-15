#include "rt.h"
#include <stdio.h>

static t_mlx	*fill_color(t_mlx *mlx)
{
	int	x;
	int	y;

	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img)
	{
		printf("failed to create an image\n");
		destroy_mlx(mlx);
		return (NULL);
	}
	mlx->addr = mlx_get_data_addr(
		mlx->img,
		&mlx->bpp,
		&mlx->line_len,
		&mlx->endian
	);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(mlx, x, y, BLUE_COLOR);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc > 2)
	{
		printf("usage: %s [scene.rt]\n", argv[0]);
		return (1);
	}
	(void)argv;
	mlx = init_mlx();
	if (mlx == NULL)
	{
		printf("failed to initialize the connection with minilibx\n");
		return (1);
	}
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (mlx->win == NULL)
	{
		printf("failed to create the window\n");
		destroy_mlx(mlx);
		return (1);
	}
	if (fill_color(mlx) == NULL)
		return (1);
	mlx_loop(mlx->mlx);
	destroy_mlx(mlx);
	return (0);
}
