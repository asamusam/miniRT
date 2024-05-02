/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:33:50 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/02 16:12:41 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_fov(int fov)
{
	if (fov < 0 || fov > 180)
		return (FAIL);
	return (SUCCESS);
}

int	check_color(t_color *color)
{
	if (color->red < 0 || color->red > 255)
		return (FAIL);
	if (color->green < 0 || color->green > 255)
		return (FAIL);
	if (color->blue < 0 || color->blue > 255)
		return (FAIL);
	return (SUCCESS);
}

int	check_intensity(float intensity)
{
	if (intensity < 0.0 || intensity > 1.0)
		return (FAIL);
	return (SUCCESS);
}

int	check_normalized_vector(t_tuple *vector)
{
	if (vector->x < -1.0 || vector->x > 1.0)
		return (FAIL);
	if (vector->y < -1.0 || vector->y > 1.0)
		return (FAIL);
	if (vector->z < -1.0 || vector->z > 1.0)
		return (FAIL);
	return (SUCCESS);
}
