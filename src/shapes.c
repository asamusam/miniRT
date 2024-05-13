/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:57:41 by llai              #+#    #+#             */
/*   Updated: 2024/05/10 23:56:56 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/shapes.h"
#include "../includes/debug.h"
#include "../includes/ray.h"
#include "../includes/matrix.h"

t_sphere	*malloc_sphere(void)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	malloc_errcheck(s);
	s->o_center = point(0, 0, 0);
	s->radius = 1;
	s->material = material();
	return (s);
}

// Calculate the ray and sphere intersecting points t1 & t2.
// Negative number means the point is behind the ray origin
int	calc_t(t_sphere s, t_ray ray, float *t1, float *t2)
{
	t_tuple	sphere_to_ray;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	sphere_to_ray = sub_tuples(ray.origin, s.o_center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - (s.radius * s.radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	*t1 = (-b - sqrt(discriminant)) / (2 * a);
	*t2 = (-b + sqrt(discriminant)) / (2 * a);
	return (0);
}

// Idetify which one of all the intersections is visible from the ray's origin
t_shape_intersect	*hit(t_list *xs)
{
	t_shape_intersect	*res;
	t_shape_intersect	*content;

	res = NULL;
	while (xs)
	{
		content = xs->content;
		if (res == NULL)
		{
			if (content->t > 0)
				res = content;
		}
		else
		{
			if (content->t > 0 && content->t < res->t)
				res = content;
		}
		xs = xs->next;
	}
	return (res);
}

t_tuple	local_normal_at(t_object *object, t_tuple local_point)
{
	if (object->type == SPHERE)
		return (normalize(
				sub_tuples(local_point, point(0, 0, 0))));
	else if (object->type == PLANE)
		return ((t_tuple){0, 1, 0, VECTOR});
	else
		return ((t_tuple){0, 0, 0, VECTOR});
}

// For a sphere, an arrow from origin to the point is perpendicular 
// to the surface of the circle at the point where it intersects.
// Since object is assumed always at world origin and radii is 1,
// converting is needed.
t_tuple	normal_at(t_object *object, t_tuple world_pt)
{
	t_tuple		object_pt;
	t_tuple		object_normal;
	t_tuple		world_normal;
	t_matrix	*inv_m;
	t_matrix	*trans_m;

	inv_m = inverse(*object->transform);
	object_pt = matrix_tuple_multiply(*inv_m, world_pt);
	object_normal = local_normal_at(object, object_pt);
	trans_m = transpose(*inv_m);
	world_normal = matrix_tuple_multiply(
			*trans_m, object_normal);
	world_normal.w = 0;
	free_matrix(&inv_m);
	free_matrix(&trans_m);
	return (normalize(world_normal));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	float	in_dot_norm;

	in_dot_norm = dot(in, normal);
	return (sub_tuples(in, scalar_mul_tuple(
				in_dot_norm, scalar_mul_tuple(2, normal))));
}

