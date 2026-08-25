/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:54:47 by spaipur-          #+#    #+#             */
/*   Updated: 2026/08/17 16:28:20 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "objects.h"
# include "error.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_ambient
{
    int id;
    int is_set; //flag to check for duplicate A declarations
    double ratio; //light ratio
    t_color color;
    
} t_ambient;

typedef struct s_atof
{
	float	integer_part;
	float	fraction;
	float	divisor;
	int		sign;
} t_atof;

typedef struct s_camera
{
	int id; // OBJ_camera
	int is_set;
	t_vec3 coordinates; //camera position
	t_vec3 direction;
	double fov;
} t_camera;

typedef struct s_light
{
    t_vec3 origin;
    double brightness;
    t_color color;
} t_light;

typedef struct s_scene
{
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_object *object;
} t_scene;

typedef struct s_image
{
	int	width;
	int	height;
	int	bpp;
	int	line_length;
	int	endian;
	void *mlx_img;   // MLX image pointer
	char *addr;      // MLX pixel buffer
	t_color *pixels;    // optional: your own pixel buffer
} t_image;

t_scene *parse_scene(const char *path);
void     free_scene(t_scene *scene);

//parsing
char *trim_line(t_scene *scene, char *line);
int is_skippable_line(char *line);
char **create_tokens(t_scene *scene, char *line);
int  get_expected_token_count(char *type);
int  dispatch_scene_parsing(t_scene *scene, char **tokens);
int  parse_ambient(t_scene *scene, char **tokens);
int  parse_camera(t_scene *scene, char **tokens);
int  parse_light(t_scene *scene, char **tokens);
t_object	*add_object(t_scene *scene, t_obj_type type);
int  parse_sphere(t_scene *scene, char **tokens);
int  parse_plane(t_scene *scene, char **tokens);
int  parse_cylinder(t_scene *scene, char **tokens);
int  parse_float(const char *str, double *out);
int  parse_vector(const char *str, t_vec3 *out);
int  parse_color(const char *str, t_color *out);

int validate_ratio(float ratio);
int validate_color(t_color color);
int validate_normalized_vector(t_vec3 vector);
int validate_fov(double fov);
void free_tokens(char **tokens);
size_t array_size(char **arr);
// parsing errors
int ft_err_handler(t_scene *scene, const char *msg);
void parse_error(const char *msg);

bool intersect_planes(const t_scene *scene, const t_ray *ray, t_hit *closest_hit);
bool intersect_spheres(const t_scene *scene, const t_ray *ray, t_hit *closest_hit);
bool intersect_cylinder(const t_scene *scene, const t_ray *ray, t_hit *closest_hit);
void render_scene(const t_scene *scene, t_image *img);
bool trace_ray(const t_scene *scene, const t_ray *ray, t_hit *closest_hit);
t_color shade(const t_scene *scene, const t_hit *hit);

#endif
