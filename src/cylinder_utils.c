/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:57:18 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:02:31 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shapes.h"
#include "../includes/ray.h"
#include "../includes/matrix.h"
#include "../includes/tuples.h"
#include "../libft/libft.h"
#include <math.h>

int	calc_cylinder_t(t_cylinder cy, t_ray ray, float *t1, float *t2)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;

	(void)cy;
	a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	if (fabs(a) < EPSILON)
		return (-1);
	b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
	c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	*t1 = (-b - sqrt(discriminant)) / (2 * a);
	*t2 = (-b + sqrt(discriminant)) / (2 * a);
	return (0);
}

// Check if the intersection at t is within a radius of 1 from y axis
bool	check_cap(t_ray *r, float t)
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
	float		t;

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

void	swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
