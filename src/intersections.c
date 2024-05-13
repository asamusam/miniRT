/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:38:10 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/13 16:20:53 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shapes.h"
#include "../includes/ray.h"
#include "../includes/matrix.h"
#include "../includes/debug.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <math.h>

static t_shape_intersect	*shape_intersection(float t, t_object *object)
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

// Check if the intersection at t is within a radius of 1 from y axis
static bool	check_cap(t_ray *r, float t)
{
	float	x;
	float	z;

	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	if ((x * x + z * z) <= 1)
		return (true);
	return (false);
}

void	intersect_caps(t_object *object, t_ray *ray, t_list **intersections)
{
	t_cylinder	*cy;
	float	t;

	cy = object->object;
	if (cy->closed == false || fabs(ray->direction.y) < EPSILON)
		return ;
	t = (cy->minimum - ray->origin.y) / ray->direction.y;
	if (check_cap(ray, t))
	{
		ft_lstadd_back(intersections, ft_lstnew(
				shape_intersection(t, object)));
	}
	t = (cy->maximum - ray->origin.y) / ray->direction.y;
	if (check_cap(ray, t))
	{
		ft_lstadd_back(intersections, ft_lstnew(
				shape_intersection(t, object)));
	}
}

static void	cylinder_intersect(
	t_object *object, t_list **intersections, t_ray *ray)
{
	t_cylinder	*cylinder;
	float		t1;
	float		t2;
	float		tmp;
	float		y;

	cylinder = (t_cylinder *)object->object;
	if (calc_cylinder_t(*cylinder, *ray, &t1, &t2) == -1)
		return ;
	if (t1 > t2)
	{
		tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
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
t_list	*intersect(t_object *object, t_ray ray)
{
	t_list		*intersections;
	t_matrix	*inv_m;
	t_ray		nray;

	inv_m = inverse(*object->transform);
	ray = transform(ray, *inv_m);
	free_matrix(&inv_m);
	intersections = NULL;
	if (object->type == SPHERE)
		sphere_intersect(object, &intersections, &ray);
	else if (object->type == PLANE)
		plane_intersect(object, &intersections, &ray);
	else if (object->type == CYLINDER)
	{
		nray.origin = ray.origin;
		nray.direction = normalize(ray.direction);
		cylinder_intersect(object, &intersections, &nray);
	}
	return (intersections);
}
