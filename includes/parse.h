/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:54:47 by spaipur-          #+#    #+#             */
/*   Updated: 2026/09/14 17:02:25 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "objects.h"
# include "camera.h"
# include "error.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_ambient
{
	int		id;
	int		is_set;
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_atof
{
	float	integer_part;
	float	fraction;
	float	divisor;
	int		sign;
}	t_atof;

typedef struct s_light
{
	t_vec3	origin;
	double	brightness;
	t_color	color;
}	t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_camera	initial_camera;
	t_light		light;
	t_object	*object;
}	t_scene;

t_scene		*parse_scene(const char *path);
int			parse_sphere(t_scene *scene, char **tokens);
int			parse_plane(t_scene *scene, char **tokens);
int			parse_cylinder(t_scene *scene, char **tokens);

char		*trim_line(t_scene *scene, char *line);
int			is_skippable_line(char *line);
char		**create_tokens(t_scene *scene, char *line);
int			get_expected_token_count(char *type);
int			dispatch_scene_parsing(t_scene *scene, char **tokens);
int			parse_float(const char *str, double *out);
int			parse_vector(const char *str, t_vec3 *out);
int			parse_color(const char *str, t_color *out);
int			skip_spaces(const char *str, int i);
int			validate_ratio(float ratio);
int			validate_color(t_color color);
int			validate_normalized_vector(t_vec3 vector);
int			validate_fov(double fov);
int			validate_scene(t_scene *scene);
int			validate_tokens(t_scene *scene, char **tokens);
void		free_tokens(char **tokens);
size_t		array_size(char **arr);
int			ft_err_handler(t_scene *scene, const char *msg);
bool		solve_quadratic(double a, double b, double c, t_range range,
				double *t);
void		free_scene(t_scene *scene);
#endif
