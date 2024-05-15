/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:51:05 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/15 13:15:36 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/world.h"
#include "../includes/parser.h"
#include "../includes/scene.h"
#include "../includes/shapes.h"
#include "../includes/matrix.h"

int	parse_sphere(char *line, t_data *data)
{
	int			i;
	t_sphere	*sphere;

	i = 0;
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (error_and_fail(SP, NULL, strerror(errno)));
	skip_space(&line[i], &i, NOT_REQUIRED);
	if (parse_tuple(&sphere->center, POINT, &line[i], &i) == FAIL || \
		skip_space(&line[i], &i, REQUIRED) == FAIL)
		return (free_shape_fail(SP, "Position", FORMAT_ERR, sphere));
	if (parse_float(&sphere->diameter, &line[i], &i) == FAIL || \
		skip_space(&line[i], &i, REQUIRED) == FAIL)
		return (free_shape_fail(SP, "Diameter", FORMAT_ERR, sphere));
	if (parse_color(&sphere->color, &line[i], &i) == FAIL)
		return (free_shape_fail(SP, "Color", FORMAT_ERR, sphere));
	if (check_color(&sphere->color) == FAIL)
		return (free_shape_fail(SP, "Color", RANGE_ERR, sphere));
	skip_space(&line[i], &i, NOT_REQUIRED);
	if (line[i])
		return (free_shape_fail(SP, NULL, EXTRA_ERR, sphere));
	calc_sphere(sphere, data);
	return (SUCCESS);
}

int	parse_plane(char *line, t_data *data)
{
	int			i;
	t_plane		*plane;

	i = 0;
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (error_and_fail(PL, NULL, strerror(errno)));
	skip_space(&line[i], &i, NOT_REQUIRED);
	if (parse_tuple(&plane->point, POINT, &line[i], &i) == FAIL || \
		skip_space(&line[i], &i, REQUIRED) == FAIL)
		return (free_shape_fail(PL, "Position", FORMAT_ERR, plane));
	if (parse_tuple(&plane->normal, VECTOR, &line[i], &i) == FAIL || \
		skip_space(&line[i], &i, REQUIRED) == FAIL)
		return (free_shape_fail(PL, "Normal", FORMAT_ERR, plane));
	if (check_normalized_vector(&plane->normal) == FAIL)
		return (free_shape_fail(PL, "Normal", RANGE_ERR, plane));
	if (parse_color(&plane->color, &line[i], &i) == FAIL)
		return (free_shape_fail(PL, "Color", FORMAT_ERR, plane));
	if (check_color(&plane->color) == FAIL)
		return (free_shape_fail(PL, "Color", RANGE_ERR, plane));
	if (skip_space(&line[i], &i, NOT_REQUIRED) && line[i])
		return (free_shape_fail(PL, NULL, EXTRA_ERR, plane));
	calc_plane(plane, data);
	return (SUCCESS);
}

static int	parse_cylinder_info(t_cylinder *cylinder, char *line, int *i)
{
	skip_space(&line[*i], i, NOT_REQUIRED);
	if (parse_tuple(&cylinder->center, POINT, &line[*i], i) == FAIL || \
		skip_space(&line[*i], i, REQUIRED) == FAIL)
		return (free_shape_fail(CY, "Position", FORMAT_ERR, cylinder));
	if (parse_tuple(&cylinder->axis, VECTOR, &line[*i], i) == FAIL || \
		skip_space(&line[*i], i, REQUIRED) == FAIL)
		return (free_shape_fail(CY, "Axis", FORMAT_ERR, cylinder));
	if (check_normalized_vector(&cylinder->axis) == FAIL)
		return (free_shape_fail(CY, "Axis", RANGE_ERR, cylinder));
	if (parse_float(&cylinder->diameter, &line[*i], i) == FAIL || \
		skip_space(&line[*i], i, REQUIRED) == FAIL)
		return (free_shape_fail(CY, "Diameter", FORMAT_ERR, cylinder));
	if (parse_float(&cylinder->height, &line[*i], i) == FAIL || \
		skip_space(&line[*i], i, REQUIRED) == FAIL)
		return (free_shape_fail(CY, "Height", FORMAT_ERR, cylinder));
	if (parse_color(&cylinder->color, &line[*i], i) == FAIL)
		return (free_shape_fail(CY, "Color", FORMAT_ERR, cylinder));
	if (check_color(&cylinder->color) == FAIL)
		return (free_shape_fail(CY, "Color", RANGE_ERR, cylinder));
	return (SUCCESS);
}

int	parse_cylinder(char *line, t_data *data)
{
	int			i;
	t_cylinder	*cylinder;

	i = 0;
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (error_and_fail(CY, NULL, strerror(errno)));
	if (parse_cylinder_info(cylinder, line, &i) == FAIL)
		return (FAIL);
	if (line[i])
		return (free_shape_fail(CY, NULL, EXTRA_ERR, cylinder));
	calc_cylinder(cylinder, data);
	return (SUCCESS);
}
