/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:03:57 by ybutkov           #+#    #+#             */
/*   Updated: 2026/09/07 12:54:26 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_INTERNAL_H
# define DRAW_INTERNAL_H

# include "rt.h"

typedef struct s_line_draw
{
	t_mlx	*mlx;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		color;
}			t_line_draw;

typedef struct s_coord_info
{
	int		x;
	int		y;
	int		decimals;
}			t_coord_info;

typedef struct s_line_algo
{
	int		x0;
	int		y0;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}			t_line_algo;

void	draw_line_internal(t_line_draw *line);
void	project_axis(const t_camera *camera, t_vec3 axis, int *screen_x,
			int *screen_y);
void	draw_object_markers(t_app *app);

#endif
