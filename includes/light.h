/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:21:20 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 16:38:59 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

#include "color.h"
#include "tuples.h"

typedef struct s_light
{
	t_tuple	position;
	t_color	intensity;
}	t_light;

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

t_light		point_light(t_tuple position, t_color intensity);
t_material	material(void);
t_color		lighting(t_material m, t_light l, t_tuple p, t_tuple eyev, t_tuple normalv);

#endif // !LIGHT_H
