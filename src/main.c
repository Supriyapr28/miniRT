#include "rt.h"
#include <stdio.h>
#include <stdlib.h>

static void	pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void fill_color(t_rt *rt)
{
	int x;
	int y;

	rt->img.ptr = mlx_new_image(rt->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!rt->img.ptr)
	{
		printf("failed to create a image");
		exit(1);
	}
	rt->img.addr = mlx_get_data_addr(
		rt->img.ptr,
        &rt->img.bpp,
        &rt->img.line_length,
        &rt->img.endian
	);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixel_put(&rt->img, x, y, BLUE_COLOR);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.ptr, 0, 0); // adding img to window at location (0, 0)
}

int	main(int argc, char **argv)
{
	t_rt	rt;

	if (argc > 2)
	{
		printf("usage: %s [scene.rt]\n", argv[0]);
		return (1);
	}
	(void)argv;
	rt.mlx = mlx_init();
	if (rt.mlx == NULL)
	{
		printf("failed to initialize the connection with minilibx");
		return (1);
	}
	rt.win = mlx_new_window(rt.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT"); /*rt.mlx is an instance or connection, title*/
	if (rt.win == NULL)
	{
		printf("failed to create the window");
		return (1);
	}
	fill_color(&rt);
	mlx_loop(rt.mlx); //trigger events related ESC, Quit from keyboard.
	return (0);
}
