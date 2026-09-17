/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 17:16:42 by us                #+#    #+#             */
/*   Updated: 2026/09/07 12:54:40 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

static void	render_pixel(const t_scene *scene, t_image *img, int x, int y)
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

static t_image	image_from_mlx(t_mlx *mlx)
{
	t_image	image;

	image.width = WIN_WIDTH;
	image.height = WIN_HEIGHT;
	image.bpp = mlx->bpp;
	image.line_length = mlx->line_len;
	image.endian = mlx->endian;
	image.mlx_img = mlx->img;
	image.addr = mlx->addr;
	image.pixels = NULL;
	return (image);
}

void	render_frame(t_app *app)
{
	t_image	image;
	int		x;
	int		y;

	if (app == NULL || app->mlx == NULL || app->scene == NULL)
		return ;
	image = image_from_mlx(app->mlx);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			render_pixel(app->scene, &image, x, y);
			x++;
		}
		y++;
	}
	draw_axes(app);
	mlx_put_image_to_window(app->mlx->mlx, app->mlx->win,
		app->mlx->img, 0, 0);
	draw_axes_labels(app);
}
