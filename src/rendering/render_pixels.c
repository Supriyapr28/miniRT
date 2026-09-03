/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 12:00:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/03 12:05:00 by spaipur-         ###   ########.fr       */
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

void	render_pixel(const t_scene *scene, t_image *img, int x, int y)
{
	t_ray	ray;
	t_hit	hit;
	t_color	color;
	bool	hit_any;

	ray = make_camera_ray(scene, x, y);
	hit_any = trace_ray(scene, &ray, &hit);
	if (hit_any)
		color = shade(scene, &hit);
	else
		color = (t_color){0, 0, 0};
	set_pixel(img, x, y, color);
}
