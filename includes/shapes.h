/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:55:50 by llai              #+#    #+#             */
/*   Updated: 2024/05/13 15:56:52 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "tuples.h"
# include "color.h"
# include "light.h"

typedef struct s_data		t_data;
typedef struct s_matrix		t_matrix;
typedef struct s_material	t_material;
typedef struct s_list		t_list;
typedef struct s_ray		t_ray;

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
	bool		closed;
	float		minimum;
	float		maximum;
}	t_cylinder;

typedef struct s_plane
{
	t_tuple		point;
	t_tuple		normal;
	t_color		color;
	t_material	material;
	t_matrix	*transform;
}	t_plane;

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

t_sphere			*malloc_sphere(void);
t_shape_intersect	*hit(t_list *xs);
t_tuple				normal_at(t_object *object, t_tuple world_pt);
t_tuple				reflect(t_tuple in, t_tuple normal);
t_list				*intersect(t_object *object, t_ray ray);
int					calc_sphere_t(t_sphere s, t_ray ray, float *t1, float *t2);
int					calc_cylinder_t(t_cylinder cy, t_ray ray, float *t1, float *t2);
void				calc_sphere(t_sphere *sphere, t_data *data);
void				calc_plane(t_plane *plane, t_data *data);
void				calc_cylinder(t_cylinder *cylinder, t_data *data);

#endif // !SHAPES_H
