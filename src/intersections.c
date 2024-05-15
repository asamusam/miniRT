/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:38:10 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/15 13:00:17 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shapes.h"
#include "../includes/ray.h"
#include "../includes/matrix.h"
#include "../includes/debug.h"
#include "../includes/tuples.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <math.h>

t_shape_intersect	*shape_intersection(float t, t_object *object)
{
	t_shape_intersect	*i;

	i = malloc(sizeof(t_shape_intersect));
	malloc_errcheck(i);
	i->t = t;
	i->object = object;
	return (i);
}

static void	sphere_intersect(
	t_object *object, t_list **intersections, t_ray *ray)
{
	float		t1;
	float		t2;
	t_sphere	*sphere;

	sphere = (t_sphere *)object->object;
	if (calc_sphere_t(*sphere, *ray, &t1, &t2) == -1)
		return ;
	ft_lstadd_back(intersections, ft_lstnew(
			shape_intersection(t1, object)));
	ft_lstadd_back(intersections, ft_lstnew(
			shape_intersection(t2, object)));
}

static void	plane_intersect(
	t_object *object, t_list **intersections, t_ray *ray)
{
	float		t;

	if (fabs(ray->direction.y) < EPSILON)
		return ;
	t = -ray->origin.y / ray->direction.y;
	ft_lstadd_back(intersections, ft_lstnew(
			shape_intersection(t, object)));
}

static void	cylinder_intersect(
	t_object *object, t_list **intersections, t_ray *ray)
{
	t_cylinder	*cylinder;
	float		t1;
	float		t2;
	float		y;

	cylinder = (t_cylinder *)object->object;
	if (calc_cylinder_t(*cylinder, *ray, &t1, &t2) == -1)
		return ;
	if (t1 > t2)
		swap(&t1, &t2);
	y = ray->origin.y + t1 * ray->direction.y;
	if (cylinder->minimum < y && y < cylinder->maximum)
	{
		ft_lstadd_back(intersections, ft_lstnew(
				shape_intersection(t1, object)));
	}
	y = ray->origin.y + t2 * ray->direction.y;
	if (cylinder->minimum < y && y < cylinder->maximum)
	{
		ft_lstadd_back(intersections, ft_lstnew(
				shape_intersection(t2, object)));
	}
	intersect_caps(object, ray, intersections);
}

// Create a list for the ray intersecting objects.
// Instead of moving the objects, apply the inverse of that transformation
// to the ray.
t_list	*intersect(t_object *object, t_ray *ray)
{
	t_list		*intersections;
	t_matrix	inv_m;
	t_ray		t_ray;

	inverse(&object->transform, &inv_m);
	transform(ray, &inv_m, &t_ray);
	intersections = NULL;
	if (object->type == SPHERE)
		sphere_intersect(object, &intersections, &t_ray);
	else if (object->type == PLANE)
		plane_intersect(object, &intersections, &t_ray);
	else if (object->type == CYLINDER)
		cylinder_intersect(object, &intersections, &t_ray);
	return (intersections);
}
