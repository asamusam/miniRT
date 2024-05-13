/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:31:07 by llai              #+#    #+#             */
/*   Updated: 2024/05/13 16:16:58 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "tuples.h"

typedef struct s_matrix	t_matrix;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

// t_ray	ray(t_tuple origin, t_tuple direction);
t_tuple	position(t_ray ray, float t);
void	transform(t_ray *r, t_matrix *m, t_ray *r2);

#endif // !RAY_H
