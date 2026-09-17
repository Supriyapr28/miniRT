#include "rt.h"

#ifdef __APPLE__

static void	close_mlx_display(void *ptr)
{
	(void)ptr;
}

#else

static void	close_mlx_display(void *ptr)
{
	mlx_destroy_display(ptr);
}

#endif

void	destroy_mlx(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win != NULL)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx != NULL)
	{
		close_mlx_display(mlx->mlx);
		free(mlx->mlx);
	}
	free(mlx);
}

void	destroy_app(t_app *app)
{
	if (app == NULL)
		return ;
	if (app->scene != NULL)
		free_scene(app->scene);
	destroy_mlx(app->mlx);
}