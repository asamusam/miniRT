/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:32:16 by llai              #+#    #+#             */
/*   Updated: 2024/05/07 15:48:36 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"
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
