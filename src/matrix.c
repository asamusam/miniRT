/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:47:43 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:21:53 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/matrix.h"
#include "../includes/tuples.h"
#include "../includes/debug.h"

bool	compare_matrix(t_matrix *mat1, t_matrix *mat2)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mat1->size)
	{
		j = -1;
		while (++j < mat1->size)
			if (!equal(mat1->data[i][j], mat2->data[i][j]))
				return (false);
	}
	return (true);
}

// Multiplying matrix is used to perform transformations like
// scaling, rotation, and translation.
void	matrix_multiply(t_matrix *A, t_matrix *B, t_matrix *m)
{
	int			row;
	int			col;
	int			k;

	row = -1;
	while (++row < A->size)
	{
		col = -1;
		while (++col < A->size)
		{
			k = -1;
			m->data[row][col] = 0.0;
			while (++k < A->size)
				m->data[row][col] += A->data[row][k] * B->data[k][col];
		}
	}
}

// Identity matrix is default transformation of any object in the scene.
void	init_identitymatrix(t_matrix *mat)
{
	int			i;
	int			j;

	i = -1;
	mat->size = 4;
	while (++i < mat->size)
	{
		j = -1;
		while (++j < mat->size)
		{
			if (i == j)
				mat->data[i][j] = 1.0;
			else
				mat->data[i][j] = 0.0;
		}
	}
}

void	matrix_tuple_multiply(t_matrix *A, t_tuple b, t_tuple *result)
{
	result->x = A->data[0][0] * b.x + A->data[0][1] * b.y
		+ A->data[0][2] * b.z + A->data[0][3] * b.w;
	result->y = A->data[1][0] * b.x + A->data[1][1] * b.y
		+ A->data[1][2] * b.z + A->data[1][3] * b.w;
	result->z = A->data[2][0] * b.x + A->data[2][1] * b.y
		+ A->data[2][2] * b.z + A->data[2][3] * b.w;
	result->w = A->data[3][0] * b.x + A->data[3][1] * b.y
		+ A->data[3][2] * b.z + A->data[3][3] * b.w;
}

// Matrix transposition flips a matrix over its diagonal.
// The rows becomes columns.
void	transpose(t_matrix *A, t_matrix *result)
{
	int			i;
	int			j;

	i = -1;
	while (++i < A->size)
	{
		j = -1;
		while (++j < A->size)
			result->data[j][i] = A->data[i][j];
	}
}
