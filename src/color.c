/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:52:21 by llai              #+#    #+#             */
/*   Updated: 2024/05/03 14:19:49 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <stdio.h>

void	print_color(t_color *color)
{
	printf("t - %f, r - %f, g - %f, b - %f", \
			color->transparent, color->red, color->green, color->blue);
}

t_color	color(float transparent, float red, float green, float blue)
{
	return ((t_color){transparent, red, green, blue});
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
