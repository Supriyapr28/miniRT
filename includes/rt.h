#ifndef RT_H
# define RT_H

# include "mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define BLUE_COLOR 0x0000FF

# include <stdlib.h>
# include <stdio.h>

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

int	    handle_key(int keycode, t_mlx *mlx);
int	    handle_close(t_mlx *mlx);
void	setup_hooks(t_mlx *mlx);

t_mlx	*init_mlx(void);
void	destroy_mlx(t_mlx *mlx);
void	put_pixel(t_mlx *mlx, int x, int y, int color);

int     create_image(t_mlx *mlx);
void    render_color(t_mlx *mlx, int color);
t_mlx   *fill_color(t_mlx *mlx);
t_mlx  *start_mlx(void);

#endif

