/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:31:07 by llai              #+#    #+#             */
/*   Updated: 2024/04/30 14:57:00 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
#define RAY_H

#include "tuples.h"
#include "matrix.h"

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

t_ray	ray(t_tuple origin, t_tuple direction);
t_tuple	position(t_ray ray, double t);
t_ray	transform(t_ray r, t_matrix m);

#endif // !RAY_H
