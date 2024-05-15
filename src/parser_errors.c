/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:44:32 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/15 12:41:28 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/parser.h"

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

void	check_extension(t_data *data, char *file)
{
	char	*tmp;

	tmp = ft_strrchr(file, '.');
	if (tmp && tmp[1] == 'r' && tmp[2] == 't' && !tmp[3])
		return ;
	else
	{
		error_and_fail("Configuration file", NULL, "Invalid extension");
		free_data(data);
		exit(EXIT_FAILURE);
	}
}
