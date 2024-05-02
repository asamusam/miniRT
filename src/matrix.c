/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:47:43 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 20:16:57 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matrix.h"
#include "../includes/tuples.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

t_matrix	create_matrix(int rows, int cols)
{
	t_matrix	mat;
	int			i;

	mat.rows = rows;
	mat.cols = cols;
	mat.data = (double **)malloc(rows * sizeof(double *));
	i = -1;
	while (++i < rows)
		mat.data[i] = (double *)malloc(cols * sizeof(double));
	return (mat);
}

void	free_matrix(t_matrix mat)
{
	int	i;

	i = -1;
	while (++i < mat.rows)
		free(mat.data[i]);
	free(mat.data);
}

void	print_matrix(t_matrix mat)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mat.rows)
	{
		j = -1;
		while (++j < mat.cols)
			printf("%.4f\t\t", mat.data[i][j]);
		printf("\n");
	}
}

bool	compare_matrix(t_matrix mat1, t_matrix mat2)
{
	int	i;
	int	j;

	if (mat1.rows != mat2.rows || mat1.cols != mat2.cols)
		return (false);
	i = -1;
	while (++i < mat1.rows)
	{
		j = -1;
		while (++j < mat1.cols)
			if (!equal(mat1.data[i][j], mat2.data[i][j]))
				return (false);
	}
	return (true);
}

t_matrix	matrix_multiply(t_matrix A, t_matrix B)
{
	int			row;
	int			col;
	int			k;
	t_matrix	m;

	if (A.cols != B.rows)
	{
		printf("Error: Incompatible matrices for multiplication.\n");
		exit(1);
	}
	m = create_matrix(A.rows, B.cols);
	row = -1;
	while (++row < A.rows)
	{
		col = -1;
		while (++col < B.cols)
		{
			k = -1;
			m.data[row][col] = 0.0;
			while (++k < A.cols)
				m.data[row][col] += A.data[row][k] * B.data[k][col];
		}
	}
	return (m);
}

t_matrix	identity_matrix(t_matrix m)
{
	t_matrix	i;
	t_matrix	res;

	i = create_matrix(4, 4);
	i.data[0][0] = 1;
	i.data[0][1] = 0;
	i.data[0][2] = 0;
	i.data[0][3] = 0;
	i.data[1][0] = 0;
	i.data[1][1] = 1;
	i.data[1][2] = 0;
	i.data[1][3] = 0;
	i.data[2][0] = 0;
	i.data[2][1] = 0;
	i.data[2][2] = 1;
	i.data[2][3] = 0;
	i.data[3][0] = 0;
	i.data[3][1] = 0;
	i.data[3][2] = 0;
	i.data[3][3] = 1;
	res = matrix_multiply(m, i);
	free_matrix(i);
	return (res);
}

t_matrix	init_identitymatrix(int size)
{
	t_matrix	mat;
	int			i;
	int			j;

	mat = create_matrix(size, size);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (i == j)
				mat.data[i][j] = 1.0;
			else
				mat.data[i][j] = 0.0;
		}
	}
	return (mat);
}

t_tuple	matrix_tuple_multiply(t_matrix A, t_tuple b)
{
	t_tuple	result;

	if (A.cols != 4)
	{
		printf("Error: Matrix should have 4 columns \
for tuple multiplication.\n");
		exit(1);
	}
	result.x = A.data[0][0] * b.x + A.data[0][1] * b.y
		+ A.data[0][2] * b.z + A.data[0][3] * b.w;
	result.y = A.data[1][0] * b.x + A.data[1][1] * b.y
		+ A.data[1][2] * b.z + A.data[1][3] * b.w;
	result.z = A.data[2][0] * b.x + A.data[2][1] * b.y
		+ A.data[2][2] * b.z + A.data[2][3] * b.w;
	result.w = A.data[3][0] * b.x + A.data[3][1] * b.y
		+ A.data[3][2] * b.z + A.data[3][3] * b.w;
	return (result);
}

t_matrix	transpose(t_matrix A)
{
	t_matrix	result;
	int			i;
	int			j;

	i = -1;
	result = create_matrix(A.cols, A.rows);
	while (++i < A.rows)
	{
		j = -1;
		while (++j < A.cols)
			result.data[j][i] = A.data[i][j];
	}
	return (result);
}

double	determinant(t_matrix m)
{
	double	det;
	int		column;

	det = 0;
	if (m.rows == 2 && m.cols == 2)
		det = m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
	else
	{
		column = -1;
		while (++column < m.cols)
			det += m.data[0][column] * cofactor(m, 0, column);
	}
	return (det);
}

t_matrix	init_submatrix(t_matrix m)
{
	t_matrix	sub;
	int			i;

	sub.rows = m.rows - 1;
	sub.cols = m.cols - 1;
	sub.data = (double **)malloc(sub.rows * sizeof(double *));
	i = -1;
	while (++i < sub.rows)
		sub.data[i] = (double *)malloc(sub.cols * sizeof(double));
	return (sub);
}

void	assign_sub(t_matrix *sub, t_matrix m, int rowToRemove, int colToRemove)
{
	int			i;
	int			j;
	int			sub_row;
	int			sub_col;

	sub_row = 0;
	sub_col = 0;
	i = -1;
	while (++i < m.rows)
	{
		if (i == rowToRemove)
			continue ;
		j = -1;
		while (++j < m.cols)
		{
			if (j == colToRemove)
				continue ;
			sub->data[sub_row][sub_col++] = m.data[i][j];
		}
		sub_row++;
		sub_col = 0;
	}
}

t_matrix	submatrix(t_matrix m, int rowToRemove, int colToRemove)
{
	t_matrix	sub;

	if (m.rows <= 1 || m.cols <= 1)
	{
		printf("Error: Matrix should have at least 2 rows and 2 columns.\n");
		exit(1);
	}
	sub = init_submatrix(m);
	assign_sub(&sub, m, rowToRemove, colToRemove);
	return (sub);
}

double	minor(t_matrix m, int row, int col)
{
	t_matrix	sub;
	double		det;

	sub = submatrix(m, row, col);
	det = determinant(sub);
	free_matrix(sub);
	return (det);
}

double	cofactor(t_matrix m, int row, int col)
{
	double	minor_value;

	minor_value = minor(m, row, col);
	if ((row + col) % 2 == 0)
		return (minor_value);
	return (-minor_value);
}

t_matrix	make_inv(t_matrix m, double det)
{
	t_matrix	m_inv;
	int			i;
	int			j;
	double		c;

	m_inv.rows = m.rows;
	m_inv.cols = m.cols;
	m_inv.data = (double **)malloc(m.rows * sizeof(double *));
	i = -1;
	while (++i < m.rows)
		m_inv.data[i] = (double *)malloc(m.cols * sizeof(double));
	i = -1;
	while (++i < m.rows)
	{
		j = -1;
		while (++j < m.cols)
		{
			c = cofactor(m, i, j);
			m_inv.data[j][i] = c / det;
		}
	}
	return (m_inv);
}

t_matrix	inverse(t_matrix m)
{
	t_matrix	m_inv;
	double		det;

	det = determinant(m);
	if (det == 0)
	{
		printf("Error: Matrix is not invertible.\n");
		exit(1);
	}
	m_inv = make_inv(m, det);
	return (m_inv);
}
