/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:02:51 by llai              #+#    #+#             */
/*   Updated: 2024/05/04 16:30:05 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/color.h"

// Convert x and y to center origin (0,0)
void	put_pixel(t_img *img, int x, int y, t_color color)
{
	int	new_x;
	int	new_y;
	int	color_val;

	new_x = (WIDTH / 2) + x;
	new_y = (HEIGHT / 2) - y;
	color_val = create_trgb_color(
			color.transparent, color.red, color.green, color.blue);
	put_pixel_img(img, new_x, new_y, color_val);
}

// (0, 0) starts at top left corner
void	put_pixel2(t_img *img, int x, int y, t_color color)
{
	int	color_val;

	color_val = create_trgb_color(
			color.transparent, color.red, color.green, color.blue);
	put_pixel_img(img, x, y, color_val);
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
