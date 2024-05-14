/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:47:43 by llai              #+#    #+#             */
/*   Updated: 2024/05/13 17:24:48 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/matrix.h"
#include "../includes/tuples.h"
#include "../includes/debug.h"

void	print_matrix(t_matrix *mat)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mat->size)
	{
		j = -1;
		while (++j < mat->size)
			printf("%.4f\t\t", mat->data[i][j]);
		printf("\n");
	}
}

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

// Determinant is used to determine whether or not the system has a solution.
// It the determinant is zero, then the corresponding system of equations has
// no solution.
float	determinant(t_matrix *m)
{
	float	det;
	int		column;

	det = 0;
	if (m->size == 2)
		det = m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
	else
	{
		column = -1;
		while (++column < m->size)
			det += m->data[0][column] * cofactor(m, 0, column);
	}
	return (det);
}

// A submatrix is what is left when deleting a single row and column
// from a matrix.
static void	assign_sub(
	t_matrix *sub, t_matrix *m, int rowToRemove, int colToRemove)
{
	int			i;
	int			j;
	int			sub_row;
	int			sub_col;

	sub->size = m->size - 1;
	sub_row = 0;
	sub_col = 0;
	i = -1;
	while (++i < m->size)
	{
		if (i == rowToRemove)
			continue ;
		j = -1;
		while (++j < m->size)
		{
			if (j == colToRemove)
				continue ;
			sub->data[sub_row][sub_col++] = m->data[i][j];
		}
		sub_row++;
		sub_col = 0;
	}
}

// The minor of an element at row i and col j is the determinant of 
// the submatrix at (i, j).
float	minor(t_matrix *m, int row, int col)
{
	t_matrix	sub;
	float		det;

	assign_sub(&sub, m, row, col);
	det = determinant(&sub);
	return (det);
}

// Cofactor is to check if the minors that have had their sign changed.
float	cofactor(t_matrix *m, int row, int col)
{
	float	minor_value;

	minor_value = minor(m, row, col);
	if ((row + col) % 2 == 0)
		return (minor_value);
	return (-minor_value);
}

// The idea of inverting matrices is to undo an operation.
// ie: 5 * 4 = 20 => 20 * inverse(4) or 1/4 = 5.
void	inverse(t_matrix *m, t_matrix *m_inv)
{
	float		det;
	int			i;
	int			j;
	float		c;

	det = determinant(m);
	if (det == 0)
	{
		printf("Error: Matrix is not invertible.\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	m_inv->size = m->size;
	while (++i < m->size)
	{
		j = -1;
		while (++j < m->size)
		{
			c = cofactor(m, i, j);
			m_inv->data[j][i] = c / det;
		}
	}
}
