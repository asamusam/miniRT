/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 21:15:41 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 19:14:56 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matrix.h"
#include <math.h>

double	radians(double deg)
{
	double	res;

	res = deg / 180 * M_PI;
	return (res);
}

t_matrix	translation(double x, double y, double z)
{
	t_matrix	trans;
	int			i;
	int			j;

	trans = create_matrix(4, 4);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (i == j)
				trans.data[i][j] = 1.0;
			trans.data[i][j] = 0.0;
		}
	}
	trans.data[0][3] = x;
	trans.data[1][3] = y;
	trans.data[2][3] = z;
	return (trans);
}

t_matrix	scaling(double x, double y, double z)
{
	t_matrix	scale;
	int			i;
	int			j;

	scale = create_matrix(4, 4);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (i == j)
				scale.data[i][j] = 1.0;
			scale.data[i][j] = 0.0;
		}
	}
	scale.data[0][0] = x;
	scale.data[1][1] = y;
	scale.data[2][2] = z;
	return (scale);
}

t_matrix	rotation_x(double theta)
{
	t_matrix	rot_x;
	double		cos_theta;
	double		sin_theta;

	rot_x = init_identitymatrix(4);
	cos_theta = cos(theta);
	sin_theta = sin(theta);
	rot_x.data[1][1] = cos_theta;
	rot_x.data[1][2] = -sin_theta;
	rot_x.data[2][1] = sin_theta;
	rot_x.data[2][2] = cos_theta;
	return (rot_x);
}

t_matrix	rotation_y(double theta)
{
	t_matrix	rot_y;
	double		cos_theta;
	double		sin_theta;

	rot_y = init_identitymatrix(4);
	cos_theta = cos(theta);
	sin_theta = sin(theta);
	rot_y.data[0][0] = cos_theta;
	rot_y.data[0][2] = sin_theta;
	rot_y.data[2][0] = -sin_theta;
	rot_y.data[2][2] = cos_theta;
	return (rot_y);
}

t_matrix	rotation_z(double theta)
{
	t_matrix	rot_z;
	double		cos_theta;
	double		sin_theta;

	rot_z = init_identitymatrix(4);
	cos_theta = cos(theta);
	sin_theta = sin(theta);
	rot_z.data[0][0] = cos_theta;
	rot_z.data[0][1] = -sin_theta;
	rot_z.data[1][0] = sin_theta;
	rot_z.data[1][1] = cos_theta;
	return (rot_z);
}
//
// t_matrix	shearing(double xy, double xz, double yx,
// double yz, double zx, double zy)
// {
// 	t_matrix shear;
//
// 	shear = init_identitymatrix(4);
// 	shear.data[0][1] = xy;
// 	shear.data[0][2] = xz;
// 	shear.data[1][0] = yx;
// 	shear.data[1][2] = yz;
// 	shear.data[2][0] = zx;
// 	shear.data[2][1] = zy;
// 	return (shear);
// }
