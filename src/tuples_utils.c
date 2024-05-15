/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:28:30 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:30:27 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>
#include "../includes/tuples.h"

t_tuple	point(float x, float y, float z)
{
	return ((t_tuple){x, y, z, POINT});
}

t_tuple	vector(float x, float y, float z)
{
	return ((t_tuple){x, y, z, VECTOR});
}

bool	equal(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	else
		return (false);
}

void	print_tuple1(t_tuple t)
{
	printf("tuple: x:%.2f y:%.2f z:%.2f w:%d\n", t.x, t.y, t.z, t.w);
}

bool	equal_tuple(t_tuple a, t_tuple b)
{
	return (equal(a.x, a.y) && equal(a.y, b.y)
		&& equal(a.z, b.z) && equal(a.w, b.w));
}
