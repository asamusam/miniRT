/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:39:50 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/02 15:32:34 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define FAIL 1
# define SUCCESS 0
# define REQUIRED 1
# define NOT_REQUIRED 0
# define AMB_NUM_ERR "Ambient: more than one is present in the file."
# define AMB_FRM_ERR "Ambient: unrecognised format."
# include "fcntl.h"
# include "unistd.h"
# include "color.h"
# include "tuples.h"

typedef struct s_data t_data;
// parser_utils.c

int	skip_space(const char *line, int *i, int flag);
int	parse_color(t_color *color, char *line, int *i);
int	parse_float(float *f, char *line, int *i);
int	parse_tuple(t_tuple *t, int type, char *line, int *i);

// parser_errors.c

int	error_and_fail(char *error);
int	unknown_identifier(char *line);

// parser_shapes.c

int	parse_sphere(char *line, t_data *data);
int	parse_plane(char *line, t_data *data);
int	parse_cylinder(char *line, t_data *data);

#endif
