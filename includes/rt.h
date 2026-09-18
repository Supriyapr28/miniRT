/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:11:55 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/18 10:49:13 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "parse.h"
# include "mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define BLUE_COLOR 0x0000FF

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

typedef struct s_app
{
	t_mlx		*mlx;
	t_scene		*scene;
	t_object	*selected_object;
}	t_app;

typedef struct s_image
{
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
	void	*mlx_img;
	char	*addr;
	t_color	*pixels;
}	t_image;

typedef struct s_line_draw
{
	t_mlx	*mlx;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		color;
}	t_line_draw;

typedef struct s_coord_info
{
	int		x;
	int		y;
	int		decimals;
}	t_coord_info;

typedef struct s_line_algo
{
	int		x0;
	int		y0;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}	t_line_algo;

/* hooks */
int		handle_key(int keycode, void *param);
int		handle_mouse(int button, int x, int y, void *param);
int		handle_close(void *param);
void	setup_hooks(t_app *app);
void	destroy_app(t_app *app);
void	reset_scene_state(t_app *app);

/* mlx */
t_mlx	*start_mlx(t_app *app);
t_mlx	*init_mlx(void);
void	destroy_mlx(t_mlx *mlx);
void	put_pixel(t_mlx *mlx, int x, int y, int color);

//rendering frame 
void	render_scene(t_app *app);

/* ray tracing */
t_ray	shoot_ray(const t_scene *scene, int x, int y);
bool	find_hit(const t_scene *scene, const t_ray *ray,
			t_hit *closest_hit);
bool	hit_plane(const t_plane *pl, const t_ray *ray, t_range range,
			t_hit *hit);
bool	hit_sphere(const t_sphere *sphere, const t_ray *ray, t_range range,
			t_hit *hit);
bool	hit_cylinder(const t_cylinder *cyl, const t_ray *ray, t_range range,
			t_hit *hit);
void	check_caps(const t_ray *ray, const t_cylinder *cyl, t_range range,
			t_cap_hit *best);
bool	try_cap_update(const t_ray *ray, const t_cap_params *cap,
			t_cap_hit *best);

/* lighting */
t_color	compute_color(const t_scene *scene, const t_hit *hit);
double	color_ratio(int channel);
int		clamp_channel(double value);

//draw graph
void	draw_axes(t_app *app);
void	draw_axes_labels(t_app *app);
void	draw_line_internal(t_line_draw *line);
void	project_axis(const t_camera *camera, t_vec3 axis, int *screen_x,
			int *screen_y);
void	draw_object_markers(t_app *app);
void	object_translate(t_object *object, t_vec3 delta);
void	object_rotate(t_object *object, t_vec3 axis, double angle);

#endif
