/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:39:50 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/04 13:54:12 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define REQUIRED 1
# define NOT_REQUIRED 0
# define NUM_ERR "More than one is present in the file"
# define FORMAT_ERR "Unrecognised format"
# define RANGE_ERR "Value out of range"
# define EXTRA_ERR "Extra information in the end of the line"
# define AMB "Ambient"
# define CAM "Camera"
# define LIGHT "Light"
# define SP "Sphere"
# define PL "Plane"
# define CY "Cylinder"
// # include "minirt.h"
# include "fcntl.h"
# include "unistd.h"
# include "errno.h"
# include <string.h>

typedef struct s_data	t_data;
typedef struct s_color	t_color;
typedef struct s_tuple	t_tuple;
// parser_utils.c

int		skip_space(const char *line, int *i, int flag);
int		parse_color(t_color *color, char *line, int *i);
int		parse_float(float *f, char *line, int *i);
int		parse_tuple(t_tuple *t, int type, char *line, int *i);

// parser_errors.c

int		free_shape_fail(char *object, char *part, char *error, void *shape);
int		error_and_fail(char *object, char *part, char *error);
int		unknown_identifier(char *line);

// parser_shapes.c

int		parse_sphere(char *line, t_data *data);
int		parse_plane(char *line, t_data *data);
int		parse_cylinder(char *line, t_data *data);

// parser_range.c

int		check_fov(int fov);
int		check_color(t_color *color);
int		check_intensity(float intensity);
int		check_normalized_vector(t_tuple *vector);

// ft_atof.c

int		ft_isspace(int c);
double	ft_atof(const char *str);

#endif
