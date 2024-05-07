/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:52:34 by llai              #+#    #+#             */
/*   Updated: 2024/05/07 13:50:57 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_H
# define TUPLES_H

# include <stdbool.h>

# define EPSILON 0.00001
# define TUPLES_H

typedef enum e_tuple_type
{
	VECTOR = 0,
	POINT = 1
}	t_tuple_type;

typedef struct s_tuple
{
	float			x;
	float			y;
	float			z;
	t_tuple_type	w;
}	t_tuple;

t_tuple	point(float x, float y, float z);
t_tuple	vector(float x, float y, float z);
bool	equal(float a, float b);
t_tuple	add_tuples(t_tuple lhs, t_tuple rhs);
t_tuple	sub_tuples(t_tuple lhs, t_tuple rhs);
t_tuple	negate_tuple(t_tuple tup);
t_tuple	scalar_mul_tuple(float lhs, t_tuple rhs);
t_tuple	scalar_dev_tuple(t_tuple lhs, float rhs);
float	magnitude(t_tuple vec);
t_tuple	normalize(t_tuple vec);
float	dot(t_tuple v1, t_tuple v2);
t_tuple	cross(t_tuple v1, t_tuple v2);

void	print_tuple2(t_tuple t);
bool	equal_tuple(t_tuple a, t_tuple b);

#endif // !TUPLES_H
