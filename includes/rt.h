#ifndef RT_H
# define RT_H

# include "mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define BLUE_COLOR 0x0000FF

/* MLX image buffer is the memory area where you draw pixels before showing them on the window.*/
typedef struct s_image
{
	void	*ptr; //MLX image ptr
	char	*addr; // raw pixel data
	int		bpp;  // bits per pixel
	int		line_length; // bytes per line
	int		endian; // endian format
}	t_image;


/*t_rt is the “runtime context” of miniRT.*/
typedef struct s_rt
{
    void        *mlx;        // MLX connection handle
    void        *win;        // MLX window handle
    t_image       img;         // Image buffer (your canvas)
    /* t_camera    cam;         // Camera parameters
    t_light     *lights;     // Array or list of lights
    t_object    *objects;    // Array or list of spheres, planes, cylinders
    t_scene     scene;       // Parsed scene data (optional) */
}	t_rt;

#endif
