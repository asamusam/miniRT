/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:22:30 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:22:49 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/light.h"
#include "../includes/shapes.h"
#include "../includes/world.h"

t_light	point_light(t_tuple position, float intensity, t_color color)
{
	return ((t_light){position, intensity, color});
}

t_material	material(void)
{
	t_material	m;

	m.color = color(0, 1, 1, 1);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200.0;
	return (m);
}
