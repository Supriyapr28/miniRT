/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 12:19:41 by uvadakku          #+#    #+#             */
/*   Updated: 2026/08/17 16:15:44 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "rt.h"
#include "objects.h"
#include "float.h"

static int color_to_int(t_color color)
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

static void set_pixel(t_image *img, int x, int y, t_color color)
{
	int index;
	char *dst;
	
	if (img == NULL)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	if (img->addr != NULL && img->line_length > 0 && img->bpp > 0)
	{
		index =  (y * img->line_length) + (x * (img->bpp / 8));
		dst = img->addr + index;
		*(unsigned int *)dst = (unsigned int)color_to_int(color);
	}
	else if (img->pixels != NULL)
	{
		index = (y * img->width) + x;
		img->pixels[index] = color;
	}
}

bool intersect_spheres(const t_scene *scene, const t_ray *ray, t_hit *closest_hit)
{
	t_object	*current;
	t_hit temp_hit;
	bool hit_anything = false;
	
	current = scene->object;
	while (current != NULL)
	{
		if (current->type == OBJ_SPHERE
			&& hit_sphere(&current->u.sphere, ray,
				0.001f, (float)closest_hit->t, &temp_hit))
		{
			*closest_hit = temp_hit;
			hit_anything = true;
		}
		current = current->next;
	}
	return hit_anything;
}

bool trace_ray(const t_scene *scene, const t_ray *ray, t_hit *closest_hit)
{
	closest_hit->t = DBL_MAX;
	bool hit_anything = false;

	hit_anything |= intersect_spheres(scene, ray, closest_hit);
	hit_anything |= intersect_planes(scene, ray, closest_hit);
	hit_anything |= intersect_cylinder(scene, ray, closest_hit);

	return (hit_anything);
}

void render_scene(const t_scene *scene, t_image *img)
{
	t_color pixel_color;
	
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			t_ray ray = make_camera_ray(scene, x, y);
			t_hit closest_hit;

			bool hit_anything = trace_ray(scene, &ray, &closest_hit);		
			if (hit_anything)
			{
				pixel_color = shade(scene, &closest_hit);
			}
			else
			{
				pixel_color = (t_color){0, 0, 0};
			}
			set_pixel(img, x, y, pixel_color);
		}
	}
}

