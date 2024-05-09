/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:33:59 by llai              #+#    #+#             */
/*   Updated: 2024/05/08 21:25:00 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

typedef struct s_progressbar
{
	int		total_pixels;
	int		current_pixel;
	float	progress;
}	t_progresbar;

void	malloc_errcheck(void *p);

#endif // DEBUG
