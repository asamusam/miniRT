/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:52:34 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 15:56:57 by llai             ###   ########.fr       */
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
	double			x;
	double			y;
	double			z;
	t_tuple_type	w;
}	t_tuple;

t_tuple	point(double x, double y, double z);
t_tuple	vector(double x, double y, double z);
bool	equal(double a, double b);
t_tuple	add_tuples(t_tuple lhs, t_tuple rhs);
t_tuple	sub_tuples(t_tuple lhs, t_tuple rhs);
t_tuple	negate_tuple(t_tuple tup);
t_tuple	scalar_mul_tuple(double lhs, t_tuple rhs);
t_tuple	scalar_dev_tuple(t_tuple lhs, double rhs);
double	magnitude(t_tuple vec);
t_tuple	normalize(t_tuple vec);
double	dot(t_tuple v1, t_tuple v2);
t_tuple	cross(t_tuple v1, t_tuple v2);

void	print_tuple(t_tuple t);

#endif // !TUPLES_H
