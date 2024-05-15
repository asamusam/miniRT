/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:29:26 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:30:08 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tuples.h"

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
