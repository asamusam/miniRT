/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:07:58 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 18:57:23 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

#include "shapes.h"
#include "tuples.h"

typedef struct s_world
{
	int			obj_nb;
	t_sphere	*spheres;
	// t_list		*spheres;
	t_light		light;
}	t_world;

typedef struct s_comps
{
	double	t;
	t_sphere	sphere;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
	bool		inside;
}	t_comps;

t_world	world(void);
t_world	default_world(void);
t_list *intersect_world(t_world world, t_ray ray);
t_comps	prepare_computations(t_intersection intersection, t_ray ray);
t_color	shade_hit(t_world world, t_comps comps);
t_color	color_at(t_world world, t_ray ray);

#endif // !WORLD_H
