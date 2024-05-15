/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:20:08 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:21:51 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/matrix.h"
#include "../includes/debug.h"

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
