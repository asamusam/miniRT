/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:52:21 by llai              #+#    #+#             */
/*   Updated: 2024/04/30 21:30:42 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/color.h"

t_color	color(double transparent, double red, double green, double blue)
{
	return ((t_color){transparent, red, green, blue});
}

t_color	add_colors(t_color c1, t_color c2)
{
	t_color	res;

	res.transparent = c1.transparent + c2.transparent;
	res.red = c1.red + c2.red;
	res.green = c1.green + c2.green;
	res.blue = c1.blue + c2.blue;
	return (res);
}

t_color	sub_colors(t_color c1, t_color c2)
{
	t_color	res;

	res.transparent = c1.transparent - c2.transparent;
	res.red = c1.red - c2.red;
	res.green = c1.green - c2.green;
	res.blue = c1.blue - c2.blue;
	return (res);
}

t_color	mul_color(t_color c, double scalar)
{
	t_color	res;

	res.transparent = c.transparent * scalar;
	res.red = c.red * scalar;
	res.green = c.green * scalar;
	res.blue = c.blue * scalar;
	return (res);

}

t_color	hadamard_product(t_color c1, t_color c2)
{
	t_color	res;

	res.transparent = c1.transparent * c2.transparent;
	res.red = c1.red * c2.red;
	res.green = c1.green * c2.green;
	res.blue = c1.blue * c2.blue;
	return (res);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	limit_color(double color)
{
	if (color >= 255)
		return (255);
	else if (color <= 0)
		return (0);
	else
		return (color);
}

int	create_trgb_color(double t, double r, double g, double b)
{

	int	it;
	int	ir;
	int	ig;
	int	ib;

	t = t * 255;
	r = r * 255;
	g = g * 255;
	b = b * 255;

	it = limit_color(t);
	ir = limit_color(r);
	ig = limit_color(g);
	ib = limit_color(b);

	return (it << 24 | ir << 16 | ig << 8 | ib);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
