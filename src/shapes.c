/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:57:41 by llai              #+#    #+#             */
/*   Updated: 2024/05/07 19:26:42 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shapes.h"
#include "../includes/error.h"
#include "../includes/ray.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdlib.h>

t_sphere	*malloc_sphere(void)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	malloc_errcheck(s);
	s->o_center = point(0, 0, 0);
	s->radius = 1;
	s->transform = init_identitymatrix(4);
	s->material = material();
	return (s);
}

t_intersection	*intersection(float t, t_sphere object)
{
	t_intersection	*i;

	i = malloc(sizeof(t_intersection));
	malloc_errcheck(i);
	i->t = t;
	i->object = object;
	return (i);
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

// Create a list for the ray intersecting spheres and its t1 & t2
// Instead of moving the sphere, apply the inverse of that transformation
// to the ray.
t_list	*intersect(t_sphere *s, t_ray ray)
{
	t_list		*interections_list;
	float		t1;
	float		t2;
	t_matrix	*inv_m;

	inv_m = inverse(*s->transform);
	ray = transform(ray, *inv_m);
	free_matrix(inv_m);
	interections_list = NULL;
	if (calc_t(*s, ray, &t1, &t2) == -1)
		return (interections_list);
	ft_lstadd_back(&interections_list, ft_lstnew(intersection(t1, *s)));
	ft_lstadd_back(&interections_list, ft_lstnew(intersection(t2, *s)));
	return (interections_list);
}

// Idetify which one of all the intersections is visible from the ray's origin
t_intersection	*hit(t_list *xs)
{
	t_intersection	*res;
	t_intersection	*content;

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

// For a sphere, an arrow from origin to the point is perpendicular 
// to the surface of the circle at the point where it intersects.
// Since object is assumed always at world origin and radii is 1,
// converting is needed.
t_tuple	normal_at(t_sphere s, t_tuple world_pt)
{
	t_tuple	object_pt;
	t_tuple	object_normal;
	t_tuple	world_normal;
	t_matrix	*inv_m;
	t_matrix	*trans_m;

	inv_m = inverse(*s.transform);
	object_pt = matrix_tuple_multiply(*inv_m, world_pt);
	object_normal = sub_tuples(object_pt, point(0, 0, 0));
	trans_m = transpose(*inv_m);
	world_normal = matrix_tuple_multiply(
			*trans_m, object_normal);
	world_normal.w = 0;
	free_matrix(inv_m);
	free_matrix(trans_m);
	return (normalize(world_normal));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	float	in_dot_norm;

	in_dot_norm = dot(in, normal);
	return (sub_tuples(in, scalar_mul_tuple(
				in_dot_norm, scalar_mul_tuple(2, normal))));
}
