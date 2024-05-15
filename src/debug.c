/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:32:16 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:18:52 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/debug.h"
#include "../includes/matrix.h"
#include <stdio.h>
#include <stdlib.h>

void	malloc_errcheck(void *p)
{
	if (!p)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
}

void	print_progress(float progress)
{
	int	bar_len;
	int	completed_len;
	int	i;

	bar_len = 20;
	completed_len = progress * bar_len;
	printf("\r[");
	i = -1;
	while (++i < completed_len)
		printf("#");
	i = completed_len;
	while (i++ < bar_len)
		printf(" ");
	printf("] %.2f%%", progress * 100);
}

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
