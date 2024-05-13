/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:32:54 by llai              #+#    #+#             */
/*   Updated: 2024/05/13 16:16:52 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray.h"
#include "../includes/matrix.h"

// t_ray	ray(t_tuple origin, t_tuple direction)
// {
// 	t_ray	r;

// 	r.origin = origin;
// 	r.direction = direction;
// 	return (r);
// }

// The position will be along the ray after t time.
t_tuple	position(t_ray ray, float t)
{
	return (add_tuples(ray.origin, (scalar_mul_tuple(t, ray.direction))));
}

void	transform(t_ray *r, t_matrix *m, t_ray *r2)
{
	matrix_tuple_multiply(m, r->origin, &r2->origin);
	matrix_tuple_multiply(m, r->direction, &r2->direction);
}
