/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:44:32 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/02 19:29:51 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_shape_status(void *shape, int status)
{
	if (status == SUCCESS)
		return (SUCCESS);
	free(shape);
	return (FAIL);
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
