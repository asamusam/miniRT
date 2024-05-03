/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:55:55 by llai              #+#    #+#             */
/*   Updated: 2024/05/03 17:14:58 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>
#include "../includes/tuples.h"

bool	equal(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	else
		return (false);
}

t_tuple	point(float x, float y, float z)
{
	return ((t_tuple){x, y, z, POINT});
}

t_tuple	vector(float x, float y, float z)
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

t_tuple	scalar_mul_tuple(float lhs, t_tuple rhs)
{
	t_tuple	res;

	res.x = lhs * rhs.x;
	res.y = lhs * rhs.y;
	res.z = lhs * rhs.z;
	res.w = lhs * rhs.w;
	return (res);
}

t_tuple	scalar_dev_tuple(t_tuple lhs, float rhs)
{
	t_tuple	res;

	res.x = lhs.x / rhs;
	res.y = lhs.y / rhs;
	res.z = lhs.z / rhs;
	res.w = lhs.w / rhs;
	return (res);
}

// Magnitude, or length, is the distance represented by a vector.
// It's how far you would travel in a straight line if you were
// to walk from one end of the vector to the other.
float	magnitude(t_tuple vec)
{
	return (sqrt(vec.x * vec.x
			+ vec.y * vec.y
			+ vec.z * vec.z
			+ vec.w * vec.w));
}

// Vectors with magnitude of 1 are called a unit vectors.
// Normalization takes an arbitrary vector and converts it into a unit vector.
t_tuple	normalize(t_tuple vec)
{
	t_tuple	res;

	res.x = vec.x / magnitude(vec);
	res.y = vec.y / magnitude(vec);
	res.z = vec.z / magnitude(vec);
	res.w = vec.w / magnitude(vec);
	return (res);
}

// Dot product (scalar product, or inner product)
// Smaller return value means larger angle between the vectors.
// The dot product without normalization takes into account 
// both the direction and magnitude of the vectors .
// While the dot product with normalization only considers the direction.
// ie: 1 means the vectors are identical, 
// -1 means they point in opposite directions.
float	dot(t_tuple v1, t_tuple v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

// Cross product produces a new vector which is perpendicular to 
// both of the original vectors.
// It measuers the "rotation" needed 
// to align one vector with another in 3D space.
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
