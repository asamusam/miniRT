/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:07:58 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 17:27:47 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

#include "shapes.h"

typedef struct s_world
{
	int			obj_nb;
	t_sphere	*spheres;
	// t_list		*spheres;
	t_light		light;
}	t_world;

t_world	world(void);
t_world	default_world(void);
t_list *intersect_world(t_world world, t_ray ray);

#endif // !WORLD_H
