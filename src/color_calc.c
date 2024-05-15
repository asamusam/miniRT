/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:52:44 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 12:52:52 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/color.h"

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

t_color	mul_color(t_color c, float scalar)
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
