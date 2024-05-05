/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:21:20 by llai              #+#    #+#             */
/*   Updated: 2024/05/05 02:28:44 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "color.h"
# include "tuples.h"

typedef struct s_world	t_world;
typedef struct s_comps	t_comps;

typedef struct s_ambient
{
	float		intensity;
	t_color		color;
}	t_ambient;

typedef struct s_light
{
	t_tuple		position;
	float		intensity;
	t_color		color;
}	t_light;

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

t_light		point_light(t_tuple position, float intensity, t_color color);
t_material	material(void);
t_color		lighting(t_world w, t_comps c);

#endif // !LIGHT_H
