/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:02:51 by llai              #+#    #+#             */
/*   Updated: 2024/04/26 15:16:11 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"

// Convert x and y to center origin (0,0)
void	put_pixel(t_img img, int x, int y, int color)
{
	int	new_x;
	int	new_y;

	new_x = (WIDTH / 2) + x;
	new_y = (HEIGHT / 2) - y;
	put_pixel_img(img, new_x, new_y, color);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int *)dst = color;
}

t_img	new_img(int width, int height, t_win window)
{
	t_img	image;

	image.win = window;
	image.img_ptr = mlx_new_image(window.mlx, width, height);
	image.addr = mlx_get_data_addr(image.img_ptr,
			&(image.bpp), &(image.line_len), &(image.endian));
	image.w = width;
	image.h = height;
	return (image);
}
