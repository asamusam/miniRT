/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:38:51 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/02 15:33:44 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "parser.h"

static int	skip_digits(const char *line, int *i, int flag)
{
	int	j;

	j = 0;
	if (!ft_isdigit(line[j]) && flag == REQUIRED)
		return (FAIL);
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
	int	start;
	int	j;

	start = 0;
	j = 0;
	if (skip_digits(&line[j], &j, REQUIRED) == FAIL || line[j] != ',')
		return (FAIL);
	j ++;
	color->red = ft_atoi(&line[start]);
	start = j;
	if (skip_digits(&line[j], &j, REQUIRED) == FAIL)
		return (FAIL);
	if (line[j] != ',')
		return (FAIL);
	j ++;
	color->green = ft_atoi(&line[start]);
	start = j;
	if (skip_digits(&line[j], &j, REQUIRED) == FAIL)
		return (FAIL);
	if (skip_space(&line[j], &j, REQUIRED) == FAIL)
		return (FAIL);
	color->blue = ft_atoi(&line[start]);
	*i += j;
	return (SUCCESS);
}

int	parse_float(float *f, char *line, int *i)
{
	int	j;

	j = 0;
	if (skip_digits(&line[j], &j, REQUIRED) == FAIL)
		return (FAIL);
	if (line[j] != '.')
		return (FAIL);
	j ++;
	if (skip_digits(&line[j], &j, REQUIRED) == FAIL)
		return (FAIL);
	*f = ft_atof(line);
	if (skip_space(&line[j], &j, REQUIRED) == FAIL)
		return (FAIL);
	*i += j;
	return (SUCCESS);
}

int	parse_tuple(t_tuple *t, int type, char *line, int *i);
