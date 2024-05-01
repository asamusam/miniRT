/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:55:55 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 14:01:57 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>
# include "../includes/tuples.h"

bool	equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	else
		return (false);
}

t_tuple	point(double x, double y, double z)
{
	return ((t_tuple){x, y, z, POINT});
}

t_tuple	vector(double x, double y, double z)
{
	return ((t_tuple){x, y, z, VECTOR});
}

t_tuple	add_tuples(t_tuple lhs, t_tuple rhs)
{
	t_tuple	res;

	res.x = lhs.x + rhs.x;
	res.y = lhs.y + rhs.y;
	res.z = lhs.z + rhs.z;
	res.w = lhs.w + rhs.w;
	return (res);
}

t_tuple	sub_tuples(t_tuple lhs, t_tuple rhs)
{
	t_tuple	res;

	res.x = lhs.x - rhs.x;
	res.y = lhs.y - rhs.y;
	res.z = lhs.z - rhs.z;
	res.w = lhs.w - rhs.w;
	return (res);
}

t_tuple	negate_tuple(t_tuple tup)
{
	t_tuple	res;

	res.x = -tup.x;
	res.y = -tup.y;
	res.z = -tup.z;
	res.w = -tup.w;
	return (res);
}

t_tuple	scalar_mul_tuple(double lhs, t_tuple rhs)
{
	t_tuple	res;

	res.x = lhs * rhs.x;
	res.y = lhs * rhs.y;
	res.z = lhs * rhs.z;
	res.w = lhs * rhs.w;
	return (res);
}

t_tuple	scalar_dev_tuple(t_tuple lhs, double rhs)
{
	t_tuple	res;

	res.x = lhs.x / rhs;
	res.y = lhs.y / rhs;
	res.z = lhs.z / rhs;
	res.w = lhs.w / rhs;
	return (res);
}

double	magnitude(t_tuple vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w));
}

t_tuple	normalize(t_tuple vec)
{
	t_tuple	res;

	res.x = vec.x / magnitude(vec);
	res.y = vec.y / magnitude(vec);
	res.z = vec.z / magnitude(vec);
	res.w = vec.w / magnitude(vec);
	return (res);
}

double	dot(t_tuple v1, t_tuple v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

t_tuple	cross(t_tuple v1, t_tuple v2)
{
	t_tuple	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	res.w = VECTOR;
	return (res);
}

void	print_tuple(t_tuple t)
{
	printf("tuple: x:%.2f y:%.2f z:%.2f w:%d\n", t.x, t.y, t.z, t.w);
}
