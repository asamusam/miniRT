/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:45:55 by llai              #+#    #+#             */
/*   Updated: 2024/05/14 19:53:34 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# define EPSILON 0.00001

# include "stdbool.h"

typedef struct s_tuple	t_tuple;

typedef struct s_matrix
{
	int		size;
	float	data[4][4];
}	t_matrix;

void		print_matrix(t_matrix *mat);
bool		compare_matrix(t_matrix *mat1, t_matrix *mat2);
void		matrix_multiply(t_matrix *A, t_matrix *B, t_matrix *m);
void		matrix_tuple_multiply(t_matrix *A, t_tuple b, t_tuple *result);
void		init_identitymatrix(t_matrix *mat);
void		transpose(t_matrix *A, t_matrix *result);
float		determinant(t_matrix *m);
float		minor(t_matrix *m, int row, int col);
float		cofactor(t_matrix *m, int row, int col);
void		inverse(t_matrix *m, t_matrix *m_inv);

// matrix_transform.c
float		radians(float deg);
void		translation(float x, float y, float z, t_matrix *trans);
void		scaling(float x, float y, float z, t_matrix *scale);
void		rotation_x(float theta, t_matrix *rot_x);
void		rotation_y(float theta, t_matrix *rot_y);
void		rotation_z(float theta, t_matrix *rot_z);

#endif // !MATRIX_H
