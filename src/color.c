/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:52:21 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 12:54:25 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/color.h"

t_color	color(float transparent, float red, float green, float blue)
{
	return ((t_color){transparent, red, green, blue});
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	limit_color(float color)
{
	if (color >= 255)
		return (255);
	else if (color <= 0)
		return (0);
	else
		return (color);
}

int	create_trgb_color(float t, float r, float g, float b)
{
	int	it;
	int	ir;
	int	ig;
	int	ib;

	t = t / 255;
	r = r / 255;
	g = g / 255;
	b = b / 255;
	it = limit_color(t);
	ir = limit_color(r);
	ig = limit_color(g);
	ib = limit_color(b);
	return (it << 24 | ir << 16 | ig << 8 | ib);
}
