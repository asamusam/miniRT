/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 21:15:41 by llai              #+#    #+#             */
/*   Updated: 2024/05/13 17:25:46 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matrix.h"
#include <math.h>

float	radians(float deg)
{
	float	res;

	res = deg / 180 * M_PI;
	return (res);
}

void	translation(float x, float y, float z, t_matrix *trans)
{
	int			i;
	int			j;

	i = -1;
	while (++i < trans->size)
	{
		j = -1;
		while (++j < trans->size)
		{
			if (i == j)
				trans->data[i][j] = 1.0;
			else
				trans->data[i][j] = 0.0;
		}
	}
	trans->data[0][3] = x;
	trans->data[1][3] = y;
	trans->data[2][3] = z;
}

void	scaling(float x, float y, float z, t_matrix *scale)
{
	int			i;
	int			j;

	i = -1;
	while (++i < scale->size)
	{
		j = -1;
		while (++j < scale->size)
		{
			if (i == j)
				scale->data[i][j] = 1.0;
			else
				scale->data[i][j] = 0.0;
		}
	}
	scale->data[0][0] = x;
	scale->data[1][1] = y;
	scale->data[2][2] = z;
}

// we don't use this function right now
void	rotation_x(float theta, t_matrix *rot_x)
{
	float		cos_theta;
	float		sin_theta;

	init_identitymatrix(rot_x);
	cos_theta = cos(theta);
	if (cos_theta < EPSILON)
		cos_theta = 0;
	sin_theta = sin(theta);
	if (sin_theta < EPSILON)
		sin_theta = 0;
	rot_x->data[1][1] = cos_theta;
	rot_x->data[1][2] = -sin_theta;
	rot_x->data[2][1] = sin_theta;
	rot_x->data[2][2] = cos_theta;
}

// we don't use this function right now
void	rotation_y(float theta, t_matrix *rot_y)
{
	float		cos_theta;
	float		sin_theta;

	init_identitymatrix(rot_y);
	cos_theta = cos(theta);
	if (cos_theta < EPSILON)
		cos_theta = 0;
	sin_theta = sin(theta);
	if (sin_theta < EPSILON)
		sin_theta = 0;
	rot_y->data[0][0] = cos_theta;
	rot_y->data[0][2] = sin_theta;
	rot_y->data[2][0] = -sin_theta;
	rot_y->data[2][2] = cos_theta;
}

// we don't use this function right now
void	rotation_z(float theta, t_matrix *rot_z)
{
	float		cos_theta;
	float		sin_theta;

	init_identitymatrix(rot_z);
	cos_theta = cos(theta);
	if (cos_theta < EPSILON)
		cos_theta = 0;
	sin_theta = sin(theta);
	if (sin_theta < EPSILON)
		sin_theta = 0;
	rot_z->data[0][0] = cos_theta;
	rot_z->data[0][1] = -sin_theta;
	rot_z->data[1][0] = sin_theta;
	rot_z->data[1][1] = cos_theta;
}
