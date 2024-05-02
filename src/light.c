/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:22:41 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 16:09:25 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/light.h"
#include "../includes/shapes.h"
#include <math.h>

t_light	point_light(t_tuple position, t_color color)
{
	return ((t_light){position, 0, color});
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

t_color	lighting(t_material m, t_light l, t_tuple p, t_tuple eyev, t_tuple normalv)
{
	t_color	effective_color;
	t_tuple	lightv;
	t_tuple	reflectv;
	double	light_dot_normal;
	double	reflect_dot_eye;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	double	factor;

	effective_color = hadamard_product(m.color, l.color);
	lightv = normalize(sub_tuples(l.position, p));
	ambient = mul_color(effective_color, m.ambient);
	light_dot_normal = dot(lightv, normalv);

	if (light_dot_normal < 0)
	{
		diffuse = color(0, 0, 0, 0);
		specular = color(0, 0, 0, 0);
	}
	else
	{
		diffuse = mul_color(mul_color(effective_color, m.diffuse), light_dot_normal);
		reflectv = reflect(negate_tuple(lightv), normalv);
		reflect_dot_eye = dot(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = color(0, 0, 0, 0);
		else
		{
			factor = pow(reflect_dot_eye, m.shininess);
			specular = mul_color(mul_color(l.color, m.specular), factor);
		}
	}

	return (add_colors(ambient, add_colors(diffuse, specular)));
}
