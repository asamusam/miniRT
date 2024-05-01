/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:02:51 by llai              #+#    #+#             */
/*   Updated: 2024/04/30 21:34:57 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"
# include "../includes/color.h"

// Convert x and y to center origin (0,0)
void	put_pixel(t_img img, int x, int y, t_color color)
{
	int	new_x;
	int	new_y;
	int	color_val;

	new_x = (WIDTH / 2) + x;
	new_y = (HEIGHT / 2) - y;
	color_val = create_trgb_color(color.transparent, color.red, color.green, color.blue);
	put_pixel_img(img, new_x, new_y, color_val);
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
