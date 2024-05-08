/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalized.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:32:17 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/08 13:44:10 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERALIZED_H
# define GENERALIZED_H

# include "minirt.h"

typedef enum e_object_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_object_type;

typedef struct s_object
{
	int			type;
	t_color		color;
	t_material	material;
	t_matrix	*transform;
	void		*object;
}	t_object;

typedef struct s_shape_intersect
{
	float		t;
	t_object	*object;
}	t_shape_intersect;

typedef struct s_shape_comps
{
	float		t;
	t_object	*object;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
	bool		inside;
}	t_shape_comps;

void	init_objects(t_data *data);
void	init_sphere_objects(t_data *data);
void	init_plane_objects(t_data *data);
t_list	*shape_intersect(t_object *obj, t_ray ray);
t_color	shape_color_at(t_world world, t_ray ray);



#endif