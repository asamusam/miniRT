/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:38:51 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/04 14:10:01 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	skip_digits(const char *line, int *i, int flag)
{
	int	j;

	j = 0;
	if (flag == REQUIRED)
	{
		if (line[j] == '+' || line[j] == '-')
			j ++;
		if (!ft_isdigit(line[j]))
			return (FAIL);
	}
	while (ft_isdigit(line[j]))
		j ++;
	*i += j;
	return (SUCCESS);
}

int	skip_space(const char *line, int *i, int flag)
{
	int	j;

	j = 0;
	if (!ft_isspace(line[j]) && flag == REQUIRED)
		return (FAIL);
	while (ft_isspace(line[j]))
		j ++;
	*i += j;
	return (SUCCESS);
}

int	parse_color(t_color *color, char *line, int *i)
{
	int	j;

	j = 0;
	if (parse_float(&color->red, &line[j], &j) == FAIL || line[j] != ',')
		return (FAIL);
	j ++;
	if (parse_float(&color->green, &line[j], &j) == FAIL || line[j] != ',')
		return (FAIL);
	j ++;
	if (parse_float(&color->blue, &line[j], &j) == FAIL || \
		(line[j] && skip_space(&line[j], &j, REQUIRED) == FAIL))
		return (FAIL);
	color->transparent = 0.0;
	*i += j;
	return (SUCCESS);
}

int	parse_float(float *f, char *line, int *i)
{
	int	j;

	j = 0;
	if (skip_digits(&line[j], &j, REQUIRED) == FAIL)
		return (FAIL);
	if (line[j] == '.')
	{
		j ++;
		if (skip_digits(&line[j], &j, REQUIRED) == FAIL)
			return (FAIL);
	}
	*f = ft_atof(line);
	*i += j;
	return (SUCCESS);
}

int	parse_tuple(t_tuple *t, int type, char *line, int *i)
{
	int	j;

	j = 0;
	t->w = type;
	if (parse_float(&t->x, &line[j], &j) == FAIL || line[j] != ',')
		return (FAIL);
	j ++;
	if (parse_float(&t->y, &line[j], &j) == FAIL || line[j] != ',')
		return (FAIL);
	j ++;
	if (parse_float(&t->z, &line[j], &j) == FAIL || !ft_isspace(line[j]))
		return (FAIL);
	*i += j;
	return (SUCCESS);
}
