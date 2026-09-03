/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:11:55 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 14:11:57 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "mlx.h"
# include "objects.h"
# include "camera.h"
# include "parse.h"

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
	t_mlx	*mlx;
	t_scene	*scene;
}	t_app;

typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

/* hooks */
int		handle_key(int keycode, void *param);
int		handle_close(void *param);
void	setup_hooks(t_app *app);
void	destroy_app(t_app *app);

/* mlx */
t_mlx	*init_mlx(void);
void	destroy_mlx(t_mlx *mlx);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
int		create_image(t_mlx *mlx);
t_mlx	*start_mlx(t_app *app);
void	render_color(t_mlx *mlx, const t_scene *scene);
void	render_frame(t_app *app);

/* ray tracing */
t_ray	make_camera_ray(const t_scene *scene, int x, int y);
t_vec3	ray_at(t_ray ray, double t);
double	ray_plane_intersection(t_ray ray, t_vec3 plane_point,
			t_vec3 plane_normal);
bool	hit_sphere(const t_sphere *sphere, const t_ray *ray, t_range range,
			t_hit *hit);
bool	hit_cylinder(const t_cylinder *cyl, const t_ray *ray, t_range range,
			t_hit *hit);
bool	hit_plane(const t_plane *pl, const t_ray *ray, t_range range,
			t_hit *hit);
void	check_caps(const t_ray *ray, const t_cylinder *cyl, t_range range,
			t_cap_hit *best);
bool	try_cap_update(const t_ray *ray, const t_cap_params *cap,
			t_cap_hit *best);

/* rendering helpers */
void	render_pixel(const t_scene *scene, t_image *img, int x, int y);
t_ray	make_shadow_ray(const t_hit *hit, const t_scene *scene);
double	color_ratio(int channel);
int		clamp_channel(double value);

#endif
