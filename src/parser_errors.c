/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:44:32 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/04 14:07:22 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	free_shape_fail(char *object, char *part, char *error, void *shape)
{
	free(shape);
	return (error_and_fail(object, part, error));
}

int	error_and_fail(char *object, char *part, char *error)
{
	if (object && part)
		printf("Error\n%s: %s: %s\n", object, part, error);
	else if (object)
		printf("Error\n%s: %s\n", object, error);
	else
		printf("Error\n%s\n", error);
	return (FAIL);
}

int	unknown_identifier(char *line)
{
	int	i;

	i = 0;
	while (!ft_isspace(line[i]))
		i++;
	line[i] = 0;
	printf("Unknown identifier: %s\n", line);
	return (FAIL);
}
