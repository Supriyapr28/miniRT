#ifndef RENDER_H
# define RENDER_H

# include "mlx.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

t_mlx	*init_mlx(void);
void	destroy_mlx(t_mlx *mlx);
void	put_pixel(t_mlx *mlx, int x, int y, int color);

#endif
