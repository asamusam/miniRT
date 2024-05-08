/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:45:55 by llai              #+#    #+#             */
/*   Updated: 2024/05/08 19:09:43 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <stdbool.h>
# include "tuples.h"

typedef struct s_matrix
{
	int		rows;
	int		cols;
	float	**data;
}	t_matrix;

// t_matrix	create_matrix(int rows, int cols);
t_matrix	*create_matrix(int rows, int cols);
// void		free_matrix(t_matrix *mat);
void		free_matrix(t_matrix **mat);
void		print_matrix(t_matrix mat);
bool		compare_matrix(t_matrix mat1, t_matrix mat2);
// t_matrix	matrix_multiply(t_matrix A, t_matrix B);
t_matrix	*matrix_multiply(t_matrix A, t_matrix B);
t_tuple		matrix_tuple_multiply(t_matrix A, t_tuple b);
// t_matrix	identity_matrix(t_matrix m);
t_matrix	*identity_matrix(t_matrix m);
// t_matrix	init_identitymatrix(int size);
t_matrix	*init_identitymatrix(int size);
t_matrix	*transpose(t_matrix A);
// float		determinant(t_matrix M);
float		determinant(t_matrix *m);
// t_matrix	submatrix(t_matrix A, int rowToRemove, int colToRemove);
// t_matrix	*submatrix(t_matrix m, int rowToRemove, int colToRemove);
t_matrix	*submatrix(t_matrix *m, int rowToRemove, int colToRemove);
// float		minor(t_matrix A, int row, int col);
float		minor(t_matrix *m, int row, int col);
// float		cofactor(t_matrix A, int row, int col);
float		cofactor(t_matrix *m, int row, int col);
// t_matrix	inverse(t_matrix M);
t_matrix	*inverse(t_matrix m);

// matrix_transform.c
float		radians(float deg);
// t_matrix	translation(float x, float y, float z);
t_matrix	*translation(float x, float y, float z);
// t_matrix	scaling(float x, float y, float z);
t_matrix	*scaling(float x, float y, float z);
t_matrix	*rotation_x(float theta);
t_matrix	*rotation_y(float theta);
t_matrix	*rotation_z(float theta);
#endif // !MATRIX_H
