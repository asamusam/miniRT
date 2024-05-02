/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:47:43 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 23:23:50 by llai             ###   ########.fr       */
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
	int	i;

	mat.rows = rows;
	mat.cols = cols;

	mat.data = (double **)malloc(rows * sizeof(double *));
	i = -1;
	while (++i < rows)
	{
		mat.data[i] = (double *)malloc(cols * sizeof(double));
	}
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
		{
			if (!equal(mat1.data[i][j], mat2.data[i][j]))
				return (false);
		}
	}
	return (true);
}

t_matrix matrix_multiply(t_matrix A, t_matrix B)
{
	int row;
	int	col;
	int	k;

    if (A.cols != B.rows) {
        printf("Error: Incompatible matrices for multiplication.\n");
        exit(1);
    }

    t_matrix M = create_matrix(A.rows, B.cols);

	row = -1;
	while (++row < A.rows)
	{
		col = -1;
		while (++col < B.cols)
		{
			k = -1;
            M.data[row][col] = 0.0;
			while (++k < A.cols)
			{
                M.data[row][col] += A.data[row][k] * B.data[k][col];
			}
		}
	}
    return M;
}

t_matrix	identity_matrix(t_matrix m)
{
	t_matrix	i = create_matrix(4, 4);

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

	t_matrix res = matrix_multiply(m, i);
	free_matrix(i);
	return (res);
}

t_matrix init_identitymatrix(int size) {
    t_matrix mat = create_matrix(size, size);

    // Initialize the matrix as an identity matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat.data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    return mat;
}

t_tuple matrix_tuple_multiply(t_matrix A, t_tuple b)
{
    if (A.cols != 4) {
        printf("Error: Matrix should have 4 columns for tuple multiplication.\n");
        exit(1);
    }

    t_tuple result;
    result.x = A.data[0][0] * b.x + A.data[0][1] * b.y + A.data[0][2] * b.z + A.data[0][3] * b.w;
    result.y = A.data[1][0] * b.x + A.data[1][1] * b.y + A.data[1][2] * b.z + A.data[1][3] * b.w;
    result.z = A.data[2][0] * b.x + A.data[2][1] * b.y + A.data[2][2] * b.z + A.data[2][3] * b.w;
    result.w = A.data[3][0] * b.x + A.data[3][1] * b.y + A.data[3][2] * b.z + A.data[3][3] * b.w;

    return result;
}

t_matrix transpose(t_matrix A)
{
    t_matrix result = create_matrix(A.cols, A.rows);
	int	i;
	int	j;

	i = -1;
	while (++i < A.rows)
	{
		j = -1;
		while (++j < A.cols)
            result.data[j][i] = A.data[i][j];
	}
    return result;
}
//
// double determinant_2x2(t_matrix mat)
// {
//     if (mat.rows != 2 || mat.cols != 2) {
//         printf("Error: Matrix should be 2x2.\n");
//         exit(1);
//     }
//
//     return mat.data[0][0] * mat.data[1][1] - mat.data[0][1] * mat.data[1][0];
// }

double determinant(t_matrix M) {
    double det = 0;

    if (M.rows == 2 && M.cols == 2) {
        det = M.data[0][0] * M.data[1][1] - M.data[0][1] * M.data[1][0];
    } else {
        for (int column = 0; column < M.cols; column++) {
            det += M.data[0][column] * cofactor(M, 0, column);
        }
    }

    return det;
}

t_matrix submatrix(t_matrix A, int rowToRemove, int colToRemove)
{
    if (A.rows <= 1 || A.cols <= 1) {
        printf("Error: Matrix should have at least 2 rows and 2 columns.\n");
        exit(1);
    }

    t_matrix sub;
    sub.rows = A.rows - 1;
    sub.cols = A.cols - 1;

    // Allocate memory for the submatrix data
    sub.data = (double **)malloc(sub.rows * sizeof(double *));
    for (int i = 0; i < sub.rows; i++) {
        sub.data[i] = (double *)malloc(sub.cols * sizeof(double));
    }

    int sub_row = 0, sub_col = 0;
    for (int i = 0; i < A.rows; i++) {
        if (i == rowToRemove) {
            continue;
        }

        for (int j = 0; j < A.cols; j++) {
            if (j == colToRemove) {
                continue;
            }
            sub.data[sub_row][sub_col++] = A.data[i][j];
        }
        sub_row++;
        sub_col = 0;
    }

    return sub;
}

double minor(t_matrix A, int row, int col)
{
    t_matrix sub = submatrix(A, row, col);
    double det = determinant(sub);
    free_matrix(sub);
    return det;
}

double cofactor(t_matrix A, int row, int col)
{
    double minor_value = minor(A, row, col);
    return ((row + col) % 2 == 0) ? minor_value : -minor_value;
}

t_matrix inverse(t_matrix M)
{
    t_matrix M_inv;

    double det = determinant(M);
    if (det == 0) {
        printf("Error: Matrix is not invertible.\n");
        exit(1);
    }

    M_inv.rows = M.rows;
    M_inv.cols = M.cols;
    M_inv.data = (double **)malloc(M.rows * sizeof(double *));
    for (int i = 0; i < M.rows; i++) {
        M_inv.data[i] = (double *)malloc(M.cols * sizeof(double));
    }

    for (int row = 0; row < M.rows; row++) {
        for (int col = 0; col < M.cols; col++) {
            double c = cofactor(M, row, col);
            M_inv.data[col][row] = c / det;
        }
    }

    return M_inv;
}
