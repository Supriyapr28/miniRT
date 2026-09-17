/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:17:32 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/14 17:38:19 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "objects.h"
#include "parse.h"
#include "draw_internal.h"
#include "camera.h"
#include <float.h>
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = color.r;
	g = color.g;
	b = color.b;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

static void	set_pixel(t_image *img, int x, int y, t_color color)
{
	int		index;
	char	*dst;

	if (img == NULL)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	if (img->addr != NULL && img->line_length > 0 && img->bpp > 0)
	{
		index = (y * img->line_length) + (x * (img->bpp / 8));
		dst = img->addr + index;
		*(unsigned int *)dst = (unsigned int)color_to_int(color);
	}
	else if (img->pixels != NULL)
	{
		index = (y * img->width) + x;
		img->pixels[index] = color;
	}
}

t_ray	shoot_ray(const t_scene *scene, int x, int y)
{
	t_camera_basis	basis;
	t_ray			ray;
	double			fov;

	ray.origin = scene->camera.coordinates;
	basis = camera_get_basis(&scene->camera);
	fov = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	ray.direction = vec3_add(basis.forward,
			vec3_scale(basis.right,
				((((double)x + 0.5) / (double)WIN_WIDTH) * 2.0 - 1.0)
				* fov * ((double)WIN_WIDTH / (double)WIN_HEIGHT)));
	ray.direction = vec3_add(ray.direction,
			vec3_scale(basis.up,
				((1.0 - (((double)y + 0.5) / (double)WIN_HEIGHT)
						* 2.0)) * fov));
	ray.direction = vec3_normalize(ray.direction);
	return (ray);
}

void	render_pixel(const t_scene *scene, t_image *img, int x, int y)
{
	t_ray	ray;
	t_hit	hit;
	t_color	color;
	bool	hit_any;

	ray = shoot_ray(scene, x, y);
	hit_any = find_hit(scene, &ray, &hit);
	if (hit_any)
		color = compute_color(scene, &hit);
	else
		color = (t_color){0, 0, 0};
	set_pixel(img, x, y, color);
}

void	render_scene(const t_scene *scene, t_image *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			render_pixel(scene, img, x, y);
			x++;
		}
		y++;
	}
}




