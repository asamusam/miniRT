/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:57:41 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 17:52:43 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shapes.h"
#include "../includes/ray.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdlib.h>

t_tuple_list	tuple_list(int count, double t1, double t2)
{
	return ((t_tuple_list){count, t1, t2});
}

t_sphere	sphere(t_tuple center, double radius)
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

t_intersection	*intersection(double t, t_sphere object)
{
	t_intersection	*i;

	i = malloc(sizeof(t_intersection));
	i->t = t;
	i->object = object;
	return (i);
}

t_list *intersect(t_sphere s, t_ray ray)
{
    // Calculate the vector from the sphere's center to the ray origin
	ray = transform(ray, inverse(s.transform));
    t_tuple sphere_to_ray = sub_tuples(ray.origin, s.center);



    // Calculate coefficients for quadratic equation
    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot(ray.direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - (s.radius * s.radius);

    // Calculate the discriminant
    double discriminant = b * b - 4 * a * c;

    // If the discriminant is negative, the ray misses the sphere
	t_list	*interections_list = NULL;
    if (discriminant < 0)
	{
		return (interections_list);
    }

    // Calculate the intersections
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);

	ft_lstadd_back(&interections_list, ft_lstnew(intersection(t1, s)));
	ft_lstadd_back(&interections_list, ft_lstnew(intersection(t2, s)));

	return (interections_list);
}

t_intersection	*hit(t_list *xs)
{
	t_intersection	*res = NULL;
	t_intersection	*content;

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

t_tuple	normal_at(t_sphere s, t_tuple world_pt)
{
	t_tuple	object_pt = matrix_tuple_multiply(inverse(s.transform), world_pt);
	t_tuple	object_normal = sub_tuples(object_pt, point(0, 0, 0));
	t_tuple	world_normal = matrix_tuple_multiply(transpose(inverse(s.transform)), object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	double	in_dot_norm = dot(in, normal);
	return (sub_tuples(in, scalar_mul_tuple(in_dot_norm, scalar_mul_tuple(2, normal))));
}
