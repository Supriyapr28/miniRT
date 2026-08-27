#ifndef RT_H
# define RT_H

# include "mlx.h"
# include "objects.h"
# include "parse.h"

# include <stdbool.h>

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
void    render_color(t_mlx *mlx, const t_scene *scene);
t_mlx   *fill_color(t_mlx *mlx, const t_scene *scene);
t_mlx  *start_mlx(const t_scene *scene);

//Math
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
double vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 a, double scalar);
double vec3_length(t_vec3 a);
t_vec3 vec3_normalize(t_vec3 a);
double vec3_abs(double value);
t_vec3 ray_at(t_ray ray, double t);
t_ray make_camera_ray(const t_scene *scene, int x, int y);
double ray_plane_intersection(t_ray ray, t_vec3 plane_point, t_vec3 plane_normal);
bool hit_sphere(const t_sphere *sphere, const t_ray *ray, float t_min, float t_max, t_hit *hit);
bool hit_cylinder(const t_cylinder *cyl, const t_ray *ray, double t_min, double t_max, t_hit *hit);
bool hit_plane(const t_plane *pl, const t_ray *ray, double t_min, double t_max, t_hit *hit);
void check_caps(const t_ray *ray, const t_cylinder * cyl, double t_min, double t_max, t_cap_hit *best);
bool try_cap_update(const t_ray *ray, const t_cap_params *cap, t_cap_hit *best);

#endif
