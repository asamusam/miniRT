/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:44:32 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/02 15:34:12 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "parser.h"

int	error_and_fail(char *error)
{
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
