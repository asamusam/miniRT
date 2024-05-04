/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:57:41 by llai              #+#    #+#             */
/*   Updated: 2024/05/04 14:12:42 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shapes.h"
#include "../includes/ray.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdlib.h>

t_tuple_list	tuple_list(int count, float t1, float t2)
{
	return ((t_tuple_list){count, t1, t2});
}

t_sphere	sphere(t_tuple center, float radius)
{
	t_sphere	s;

	s.center = center;
	s.radius = radius;
	s.transform = init_identitymatrix(4);
	s.material = material();
	return (s);
}

void	set_transform(t_sphere *shpere, t_matrix t)
{
	shpere->transform = t;
}

t_intersection	*intersection(float t, t_sphere object)
{
	t_intersection	*i;

	i = malloc(sizeof(t_intersection));
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

	sphere_to_ray = sub_tuples(ray.origin, s.center);
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
t_list	*intersect(t_sphere s, t_ray ray)
{
	t_list	*interections_list;
	float	t1;
	float	t2;

	ray = transform(ray, inverse(s.transform));
	interections_list = NULL;
	if (calc_t(s, ray, &t1, &t2) == -1)
		return (interections_list);
	ft_lstadd_back(&interections_list, ft_lstnew(intersection(t1, s)));
	ft_lstadd_back(&interections_list, ft_lstnew(intersection(t2, s)));
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

	object_pt = matrix_tuple_multiply(inverse(s.transform), world_pt);
	object_normal = sub_tuples(object_pt, point(0, 0, 0));
	world_normal = matrix_tuple_multiply(
			transpose(inverse(s.transform)), object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	float	in_dot_norm;

	in_dot_norm = dot(in, normal);
	return (sub_tuples(in, scalar_mul_tuple(
				in_dot_norm, scalar_mul_tuple(2, normal))));
}
