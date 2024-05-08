/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:55:50 by llai              #+#    #+#             */
/*   Updated: 2024/05/08 11:16:50 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "light.h"
# include "matrix.h"
# include "tuples.h"
# include "ray.h"
# include "../libft/libft.h"

typedef struct s_tuple_list
{
	int		count;
	float	t1;
	float	t2;
}	t_tuple_list;

typedef struct s_cylinder
{
	t_tuple		center;
	t_tuple		axis;
	float		diameter;
	float		height;
	t_color		color;
}	t_cylinder;

typedef struct s_plane
{
	t_tuple		point;
	t_tuple		normal;
	t_color		color;
	t_material	material;
	t_matrix	*transform;
}	t_plane;

// typedef struct s_sphere
// {
// 	t_tuple		center;
// 	float		diameter;
// 	t_color		color;
// }	t_sphere;
//
typedef struct s_sphere
{
	t_tuple		center;
	t_tuple		o_center;
	float		radius;
	float		diameter;
	t_matrix	*transform;
	t_color		color;
	t_material	material;
}	t_sphere;

typedef struct s_intersection
{
	float		t;
	t_sphere	object;
}	t_intersection;

t_sphere		sphere(t_tuple center, float radius);
t_sphere		*malloc_sphere(void);
void			set_transform(t_sphere *shpere, t_matrix t);
t_intersection	*intersection(float t, t_sphere object);
// t_list			*intersect(t_sphere sphere, t_ray ray);
t_list			*intersect(t_sphere *sphere, t_ray ray);
t_intersection	*hit(t_list *xs);
t_tuple			normal_at(t_sphere s, t_tuple p);
t_tuple			reflect(t_tuple in, t_tuple normal);

#endif // !SHAPES_H
