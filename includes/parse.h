/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:54:47 by spaipur-          #+#    #+#             */
/*   Updated: 2026/07/24 15:15:18 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../includes/objects.h"
# include "../includes/error.h"

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
    t_vec3 origin;
    t_vec3 direction;
    double fov;
} t_camera;

typedef struct s_light
{
    t_vec3 origin;
    double brightness;
    int color;
} t_light;

typedef enum e_obj_type
{
    OBJ_AMBIENT,
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER,
} t_obj_type;

typedef struct s_object
{
    t_obj_type type;
    void *data; //point to sphere or plane or cylinder   
    struct s_object *next;
}t_object;

typedef struct s_scene
{
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_object *object;
}t_scene;

t_scene *parse_scene(const char *path);
void     free_scene(t_scene *scene);

//parsing
char *trim_line(char *line);
int is_skippable_line(char *line);
char **create_tokens(char *line);
int  validate_token(char **tokens);
int  dispatch_scene_parsing(t_scene *scene, char **tokens);
int  parse_ambient(t_scene *scene, char **tokens);
int  parse_camera(t_scene *scene, char **tokens);
int  parse_light(t_scene *scene, char **tokens);
int  parse_sphere(t_scene *scene, char **tokens);
int  parse_plane(t_scene *scene, char **tokens);
int  parse_cylinder(t_scene *scene, char **tokens);
int  parse_float(const char *str, double *out);
int  parse_vector(const char *str, t_vec3 *out);
int  parse_color(const char *str, t_color *out);
void validate_color(t_color color);
void validate_vector(t_vec3 vector);

void free_tokens(char **tokens);

// parsing errors
void parse_error(const char *msg);

#endif